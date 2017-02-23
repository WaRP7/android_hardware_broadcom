#include <stdio.h>
#include "BtCtlService.h"
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "log.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

namespace android
{
	static pthread_key_t sigbuskey;
    static char rfkill_state_path[64];

	int BtCtlService::instance()
	{
		LOGE("BtCtlService instantiate");
		int r = defaultServiceManager()->addService(String16("service.add"), new BtCtlService());
		LOGE("BtCtlService r = %d/n", r);

        init_rfkill();
        return r; 
	}

	BtCtlService::BtCtlService()
	{ 
		LOGV("BtCtlService created");
        pthread_key_create(&sigbuskey, NULL);
    }

	BtCtlService::~BtCtlService()
    {
		pthread_key_delete(sigbuskey);
        LOGV("BtCtlService destroyed");
    }

    int BtCtlService::init_rfkill()
    {
        char path[64];
        char buf[16];
        int fd, sz, id;

        for (id = 0; ; id++)
        {
            snprintf(path, sizeof(path), "/sys/class/rfkill/rfkill%d/type", id);
            fd = open(path, O_RDONLY);
            if (fd < 0)
            {
                ALOGE("init_rfkill : open(%s) failed: %s (%d)\n", \
                        path, strerror(errno), errno);
                return -1;
            }

            sz = read(fd, &buf, sizeof(buf));
            close(fd);

            if (sz >= 9 && memcmp(buf, "bluetooth", 9) == 0)
            {
                //rfkill_id = id;
                break;
            }
        }

        sprintf(rfkill_state_path, "/sys/class/rfkill/rfkill%d/state", id);
        ALOGI("find bluetooth rfkill path: %s", rfkill_state_path);
        return 0;
    }


	status_t BtCtlService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        status_t ret=-1;
        char buffer='1';
        //const char* rfkill_state_path = "/sys/class/rfkill/rfkill0/state";

        switch(code)
        {
            case 0: 
            {
                LOGV("onTransact case 0\n");
                buffer='0';
                int fd = open(rfkill_state_path, O_WRONLY);
                if (fd < 0)
                {
                    ALOGE("set_bluetooth_power : open(%s) for write failed: %s (%d)",
                            rfkill_state_path, strerror(errno), errno);
                    return ret;
                }
                int sz = write(fd, &buffer, 1);

                if (sz < 0) {
                    ALOGE("set_bluetooth_power : write(%s) failed: %s (%d)",
                            rfkill_state_path, strerror(errno),errno);
                }
                else
                    ret = 0;

                if (fd >= 0)
                    close(fd);
                return ret;
            }
            break;
            case 1: 
            {
                LOGV("onTransact case 1\n");
                buffer='1';
                int fd = open(rfkill_state_path, O_WRONLY);

                if (fd < 0)
                {
                    ALOGE("set_bluetooth_power : open(%s) for write failed: %s (%d)",
                            rfkill_state_path, strerror(errno), errno);
                    return ret;
                }
                int sz = write(fd, &buffer, 1);

                if (sz < 0) {
                    ALOGE("set_bluetooth_power : write(%s) failed: %s (%d)",
                            rfkill_state_path, strerror(errno),errno);
                }
                else
                    ret = 0;

                if (fd >= 0)
                    close(fd);
                return ret;
            }
            break;

            default:
            return BBinder::onTransact(code, data, reply, flags);

        }
    } 
}


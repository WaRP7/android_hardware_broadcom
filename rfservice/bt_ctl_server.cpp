#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "log.h"
#include "BtCtlService.h"

using namespace android;

int main(int argc, char* argv[])
{
	ALOGI("bt_ctl_server begin\n");
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	//LOGI("ServiceManager: %p", sm.get());
	ALOGI("ServiceManager: %p\n", sm.get());

	int ret = BtCtlService::instance();
	ALOGI("BtCtlService instantiate return ret=%d\n", ret);

	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();

	return 0;
}


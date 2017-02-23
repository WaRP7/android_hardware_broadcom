#ifndef ANDROID_ADD_SERVICE_H
#define ANDROID_ADD_SERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android
{
	class BtCtlService : public BBinder
	{
	public:
		static int instance();
		BtCtlService();
		virtual ~BtCtlService();
		virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
    private:
        static int init_rfkill() ;
        //static char rfkill_state_path[64];
	};
}

#endif

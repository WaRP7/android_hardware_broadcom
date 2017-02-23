#include <stdio.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>
#include "BtCtl.h"

namespace android
{
	sp<IBinder> binder;
	int BtCtl::setN(int n)
	{
		printf("setN n=%d\n", n);
		getBtCtlService();
		Parcel data, reply;
		data.writeInt32(getpid());
		data.writeInt32(n);
		//LOGE("BpBtCtlService::create remote()->transact()/n");
		binder->transact(n, data, &reply);
		int i = reply.readInt32();
		
		printf("BtCtl::setN return i=%d\n", i);
		return i;
	}

	const void BtCtl::getBtCtlService()
	{
		sp<IServiceManager> sm = defaultServiceManager();
		binder = sm->getService(String16("service.add"));
		//LOGE("BtCtl::getBtCtlService %p/n",sm.get());
		printf("BtCtl::getBtCtlService %p\n", sm.get());
		if (binder == NULL)
		{
			printf("binder == 0\n");
			//LOGW("BtCtlService not published, waiting...");
			return;
		}
	}
};

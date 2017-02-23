#ifndef ANDROID_ADD_H
#define ANDROID_ADD_H

namespace android
{
	class BtCtl
	{
	public:
		int setN(int n);
	private:
		static const void getBtCtlService();
	};
}

#endif 

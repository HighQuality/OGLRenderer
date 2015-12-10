#pragma once

namespace Cog
{
	class IEventListener
	{
	public:
		virtual ~IEventListener();

		void StopListen();
		bool HasStoppedListening() const;

	protected:
		IEventListener();

	private:
		bool myHasStoppedListening;
	};
}

#pragma once

namespace Cog
{
	class Event
	{
	public:
		Event();
		virtual ~Event();

		void Interrup();
		inline bool IsInterrupted() const;

	private:
		bool myIsInterrupted;
	};

	bool Event::IsInterrupted() const
	{
		return myIsInterrupted;
	}
}

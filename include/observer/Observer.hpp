#pragma once
#ifndef _Observer_HPP_
#define _Observer_HPP_

namespace observer
{

	/// \class Observer
	/// \brief Interface for the Observer.
	class Observer
	{
	public:
		/// \brief Update the state of this observer.
		virtual void notify() = 0;
	};

} // namespace observer

#endif /* _Observer_HPP_ */
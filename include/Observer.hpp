#pragma once
#ifndef _Observer_HPP_
#define _Observer_HPP_

/// \class Observer
/// \brief Interface for the Observer.
class Observer
{
public:
	/// \brief Update the state of this observer.
	virtual void notify() = 0;
};

#endif /* _Observer_HPP_ */
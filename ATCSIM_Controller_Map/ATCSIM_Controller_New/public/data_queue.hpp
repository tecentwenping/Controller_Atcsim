#pragma once
#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/call_traits.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>


template<class T>
class data_queue{
public:
	typedef boost::circular_buffer<T> container_type;
	typedef typename container_type::size_type size_type;
	typedef typename container_type::value_type value_type;
	typedef typename boost::call_traits<value_type>::param_type param_type;

	explicit data_queue(size_type capacity):m_unread(0),m_container(capacity)
	{
		int cc = m_unread;
	}

	void write(param_type item){
		boost::mutex::scoped_lock lock(m_mutex);
		m_not_full.wait(lock,boost::bind(&data_queue<value_type>::is_not_full,this));
		m_container.push_front(item);
		++m_unread;
		lock.unlock();
		m_not_empty.notify_one();
	}
	void read(value_type * pitem){
		boost::mutex::scoped_lock lock(m_mutex);
		m_not_empty.wait(lock,boost::bind(&data_queue<value_type>::is_not_empty,this));
		*pitem = m_container[--m_unread];
		lock.unlock();
		m_not_full.notify_one();
	}
private:
	data_queue(const data_queue &);
	data_queue& operator=(const data_queue&);

	bool is_not_empty() const {return m_unread >0;}
	bool is_not_full()  const {return m_unread < m_container.capacity();}
	size_type m_unread;
	container_type m_container;
	boost::mutex m_mutex;
	boost::condition m_not_empty;//未空 信号量
	boost::condition m_not_full;//未满  信号量

};
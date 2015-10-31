#ifndef BOOST_NEW_PROGRESS_HPP
#define BOOST_NEW_PROGRESS_HPP

#include<boost/progress.hpp>
#include<boost/static_assert.hpp>
//使用模板参数实现progress_timer
template<int N = 2>
class new_progress_timer:public boost::timer
{
   public:    
	new_progress_timer(std::ostream & os = std::cout):m_os(os)
	  {
  		     BOOST_STATIC_ASSERT(N >=0 && N <= 10);
	   }

	~new_progress_timer()
      	    {
		    try
               {
		//保存流的状态
				   std::istream::fmtflags old_flages = m_os.setf(std::istream::fixed, std::istream::floatfield);
	        std::streamsize old_prec = m_os.precision(N);
	        //输出时间
	        m_os << elapsed() << " s\n"<<std::endl;
	       //恢复流状态
	       m_os.flags( old_flages );
	       m_os.precision( old_prec );
		}
	        catch(...) {}
              }
	private:
		std::ostream & m_os;
};
template<>
class new_progress_timer<2>:public boost::progress_timer
{};
#endif
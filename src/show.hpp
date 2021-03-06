#ifndef h__show__h
#define h__show__h


template <int n, typename Arg0, typename... Args>
struct args_printer
{
	static std::ostream& pp(std::ostream& strm)  {
		strm << typeid(Arg0).name() << ",";
		args_printer<n-1, Args...>::pp(strm);
		return strm;
	}
	
};

template<typename Arg0>
struct args_printer<1, Arg0>
{
	static std::ostream& pp(std::ostream& strm)  {
		strm << typeid(Arg0).name();
		return strm;
	}
};

template <typename... A>
std::ostream& typeids(std::ostream& strm) {
	args_printer<sizeof...(A), A...>::pp(strm);
	return strm;
}

template<typename T>
std::ostream& operator<<(std::ostream& strm, const std::forward_list<T>& L) 
{
  strm << "std::forward_list<" << typeid(T).name() << "> [";
  size_t index = 7;
  for (auto& v : L) {
    strm << v << ",";
    if (index % 10 == 0) {
      strm<< std::endl;
    }
  }
  return strm << "]";
}

template<typename T>
std::ostream& operator<<(std::ostream& strm, const std::list<T>& L) 
{
  strm << "std::list<" << typeid(T).name() << "> [";
  size_t index = 7;
  for (auto& v : L) {
    strm << v << ",";
    if (index % 10 == 0) {
      strm<< std::endl;
    }
  }
  return strm << "]";
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& strm, const std::pair<T,U>& p) 
{
	return strm << "(" << p.first << "," << p.second << ")";
}

//from Josuttis : The c++ standard library 2nd edition 

template <int i, int MAX, typename... args>
struct print_tuple {
  static std::ostream& pp(std::ostream& strm, const std::tuple<args...>& t) {
    strm << std::get<i>(t) << ((i+1 == MAX) ? "" : ",");
    return print_tuple<i+1, MAX, args...>::pp(strm,t);
  }
};
template<int MAX, typename... args>
struct print_tuple<MAX,MAX,args...> {
  static std::ostream& pp(std::ostream& strm, const std::tuple<args...>& t) {
    return strm;
  }
};
template<typename... args>
std::ostream& operator<<(std::ostream& strm, const std::tuple<args...>& t) {
  strm << "(";
  print_tuple<0, sizeof...(args), args...>::pp(strm,t);
  return strm<<")";
}

template <typename T>
std::ostream& operator<<(std::ostream& strm, std::shared_ptr<T> t)
{
  strm << "std::shared_ptr<" << typeid(T).name() << ">(";
  if (t) {
    return strm << *t << ")";
  }
  return strm <<  "NULL)";
}

template <typename Ret, typename... Arg>
std::ostream& operator<<(std::ostream& strm, std::function<Ret(Arg...)> F)
{
	strm << "std::function<" 
		 << typeid(Ret).name() 
		 << "(" ;
	typeids<Arg...>(strm); 
	strm << ")>";
	return strm;
}



#endif

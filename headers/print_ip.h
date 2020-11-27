/**
    \file
    \mainpage Домашнее задание №3 курса "C++ Developer. Professional" ООО «Отус онлайн-образование»
	\brief Домашнее задание №3 курса "C++ Developer. Professional" ООО «Отус онлайн-образование»
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020
	\warning Работа сделана в учебных целях

*Реализация перегрузок функции печати условного IP-адреса посредством механизма SFINAE.
*/

#ifndef PRINT_IP_H
#define PRINT_IP_H

#define _PRETTY_ __PRETTY_FUNCTION__
#if (defined NDEBUG)
#define DEBUG_MODE(x)
#else
#define DEBUG_MODE(x) (x)
#endif

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <experimental/iterator>

namespace tmp_ {

    template<typename T>
    using enable_integral_t = std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>>;


    template<typename T, template<typename> class Cont>
    using enable_contaners_t = std::enable_if_t<std::is_same_v<std::decay_t<Cont<T>>, std::vector<T>>
                                  || std::is_same_v<std::decay_t<Cont<T>>, std::list<T>>>;


    template<typename T>
    using enable_string_t = std::enable_if_t<std::is_same_v<std::decay_t<T>, std::string>>;


    template<typename T, typename... Tail>
    using enable_all_the_same_t = std::enable_if_t<std::conjunction_v<std::is_same<T, Tail>...>>;


    template<typename T, class = enable_integral_t<T>>
    class Integral_type_printer {

      public:

        Integral_type_printer() = delete;
        Integral_type_printer(const Integral_type_printer& in_param) = delete;

        Integral_type_printer(const T& in_param) :
                                    value(in_param),
                                    uchar_represent(reinterpret_cast<unsigned char*>(&value)),
                                    type_size(sizeof(T) - 1){}


        friend std::ostream& operator<<(std::ostream &cur_stream, const Integral_type_printer& in_param) {

            size_t index = in_param.type_size;

            cur_stream << in_param.get_by_idx(index);
            for(; index; cur_stream << '.' << in_param.get_by_idx(--index));

            return cur_stream;

        }

      private:

        unsigned get_by_idx(const size_t& idx) const {
            return static_cast<unsigned>(uchar_represent[idx]);
        }

        T value;
        unsigned char* uchar_represent;
        const size_t type_size;
    };


    template <typename T, typename ... Ts>
    void print_args(std::ostream &cur_stream, const T& first_arg, const Ts& ...tail_args) {

        cur_stream << first_arg;
        (void)std::initializer_list<int>{((cur_stream << '.' << tail_args), 0)...};

    }


    template <typename ... Ts>
    std::ostream& operator<<(std::ostream &cur_stream, const std::tuple<Ts...>& in_parameter) {

        auto print_to_stream = [&cur_stream](const auto &...lyambda_args) {
            print_args(cur_stream, lyambda_args...);
        };

        std::apply(print_to_stream, in_parameter);

        return cur_stream;
    }


} //namespace tmp_


/**
	\brief Печать условного IP-адреса implimentation for std::string
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020

*Включается при входном аргументе типа std::string.
*
*В результате выводится содежимое строки - как есть.
*/
template<typename T>
typename tmp_::enable_string_t<T>
  generator_ip(const T& param_) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    std::cout << param_ << std::endl;
}


/*!
	\brief Печать условного IP-адреса implimentation for integral types
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020

*Включается при входном аргументе интегрального типа, за исключением типа bool.

*Поразрядно выводится содержимое типа начиная со старшего,разделенные символом '.'.
*/

template<typename T>
typename tmp_::enable_integral_t<T>
  generator_ip(const T& in_param) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    using namespace tmp_;

    std::cout << Integral_type_printer(in_param) << std::endl;
}

/**
	\brief Печать условного IP-адреса implimentation for std::vector and std::list
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020

*Включается при входном аргументе типов std::vector и std::list.

*Последовательно выводится содержимое контейнера с разделителем - '.'.
*/

template<typename T, template<typename> class Cont>
typename tmp_::enable_contaners_t<T, Cont>
  generator_ip(const Cont<T>& param_) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    std::copy(std::begin(param_), std::end(param_), std::experimental::make_ostream_joiner(std::cout, "."));
    std::cout << std::endl;
}


/**
	\brief Печать условного IP-адреса implimentation for std::tuple
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020
	\warning Опциональное задание.

*Включается при входном аргументе типов std::tuple, у которого все элементы одинакового типа.

*Последовательно выводится содержимое контейнера с разделителем - '.'.
*/
template<typename T, typename... Tail>
typename tmp_::enable_all_the_same_t<T, Tail...>
  generator_ip(const std::tuple<T, Tail...>& in_param) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    using namespace tmp_;

    std::cout << in_param << std::endl;
}



#endif // PRINT_IP_H

/**
    \file
    \mainpage Homework ¹3 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\brief Homework ¹3 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020
	\warning This work was done for educational purposes.

*Implementing overloads of the function of printing some IP-address using SFINAE.
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
                                    byte_represent(reinterpret_cast<uint8_t*>(&value)),
                                    type_size(sizeof(T) - 1){}


        friend std::ostream& operator<<(std::ostream &cur_stream, const Integral_type_printer& in_param) {

            size_t index = in_param.type_size;

            cur_stream << in_param.get_by_idx(index);
            while(index) {
                cur_stream << '.' << in_param.get_by_idx(--index);
            }

            return cur_stream;

        }

      private:
        //here is an implicit conversion, maybe an explicit one was needed? (static_cast<unsigned>)
        unsigned get_by_idx(const size_t& idx) const {
            return byte_represent[idx];
        }

        T value;
        uint8_t* byte_represent;
        const size_t type_size;
    };


    template <typename T, typename ... Ts>
    void print_args(std::ostream &cur_stream, const T& first_arg, const Ts& ...tail_args) {

        cur_stream << first_arg;
        (void)std::initializer_list<int>{((cur_stream << '.' << tail_args), 0)...};

    }


    template <typename ... Ts>
    std::ostream& operator<<(std::ostream &cur_stream, const std::tuple<Ts...>& in_parameter) {

        auto print_to_stream = [&cur_stream](const auto&... lyambda_args) {
            print_args(cur_stream, lyambda_args...);
        };

        std::apply(print_to_stream, in_parameter);

        return cur_stream;
    }


} //namespace tmp_


/**
	\brief Printing some IP address implementation for a std::string.

*Fires with an input argument of type std::string.
*
*As a result, the content of the string is displayed as is.
*/
template<typename T>
typename tmp_::enable_string_t<T>
  generator_ip(const T& param_) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    std::cout << param_ << std::endl;
}


/*!
	\brief Printing some IP-address implementation for integral types

*Turns on when an input argument of integral type, except for bool type.

*The content of the type is displayed bit by bit, starting with the most significant, separated by the '.' character.
*/

template<typename T>
typename tmp_::enable_integral_t<T>
  generator_ip(const T& in_param) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    using namespace tmp_;

    std::cout << Integral_type_printer(in_param) << std::endl;
}

/**
	\brief Printing some IP-address implimentation for std::vector and std::list

*Turns on when an input argument of std::vector and std::list types.

*The contents of the container are displayed sequentially, separated by the '.' character.
*/

template<typename T, template<typename> class Cont>
typename tmp_::enable_contaners_t<T, Cont>
  generator_ip(const Cont<T>& param_) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    std::copy(std::begin(param_), std::end(param_), std::experimental::make_ostream_joiner(std::cout, "."));
    std::cout << std::endl;
}


/**
	\brief Printing some IP-address implimentation for a std::tuple

*Turns on when an input argument of std::tuple type has all elements of the same type.

*The contents of the container are displayed sequentially, separated by the '.' character.
*/
template<typename T, typename... Tail>
typename tmp_::enable_all_the_same_t<T, Tail...>
  generator_ip(const std::tuple<T, Tail...>& in_param) {

    DEBUG_MODE(std::cout << _PRETTY_ << std::endl);

    using namespace tmp_;

    std::cout << in_param << std::endl;
}



#endif // PRINT_IP_H

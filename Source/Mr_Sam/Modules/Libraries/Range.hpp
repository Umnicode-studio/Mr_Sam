//
// Created by anton on 4/4/20.
//

#ifndef MR_SAM_LIBRARIES_RANGE_HPP
#define MR_SAM_LIBRARIES_RANGE_HPP

namespace Libraries {
    /*!
     * \brief Datatype for storing ranges
     * @tparam T
     */
    template <typename T>
    class Range {
    public:
        T min = T();
        T max = T();

        Range(T min = T(), T max = T()){
            this->min = min;
            this->max = max;
        }
        ~Range() = default;

        Range operator+(Range<T> right){
            return Range<T> (this->min + right.min, this->max + right.max);
        }
        Range operator-(Range<T> right){
            return Range<T> (this->min - right.min, this->max - right.min);
        }

        Range operator*(Range<T> right){
            return Range<T> (this->min * right.min, this->max * right.max);
        }
        Range operator/(Range<T> right){
            return Range<T> (this->min / right.min, this->max / right.max);
        }
    };
}


#endif //MR_SAM_LIBRARIES_RANGE_HPP

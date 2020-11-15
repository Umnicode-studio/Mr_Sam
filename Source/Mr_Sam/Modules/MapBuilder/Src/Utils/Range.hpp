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
    class TRange {
    public:
        T Min = T();
        T Max = T();

        TRange(T Min = T(), T Max = T()){
            this->Min = Min;
            this->Max = Max;
        }
        ~TRange() = default;

        TRange operator+(TRange<T> Right){
            return TRange<T> (this->Min + Right.Min, this->Max + Right.Max);
        }
        TRange operator-(TRange<T> Right){
            return TRange<T> (this->Min - Right.Min, this->Max - Right.Max);
        }

        TRange operator*(TRange<T> Right){
            return TRange<T> (this->Min * Right.Min, this->Max * Right.Max);
        }
        TRange operator/(TRange<T> Right){
            return TRange<T> (this->Min / Right.Min, this->Max / Right.Max);
        }
    };
}


#endif //MR_SAM_LIBRARIES_RANGE_HPP

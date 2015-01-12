#ifndef RheologyMatrixSetter_HPP
#define RheologyMatrixSetter_HPP 

#include "libgcm/rheologyModels/GcmMatrix.hpp"
#include "libgcm/rheologyModels/Material.hpp"

#include <memory>

namespace gcm
{
    class CalcNode;

    /**
     * Interface to implement for rheology matrix setter. Setter if supposed to modify
     * rheology matrix elements depending on used rheology and plasticity model.
     */
    class RheologyMatrixSetter
    {
    public:
        /**
         * Destructor.
         */
        virtual ~RheologyMatrixSetter() = 0;
        /**
         * Returns number of matrix states after decompositions. This method is supposed to be used to
         * preallocate memory for matrices cache.
         *
         * @return Number of possible states (for one space direction) or 0 if unknown.
         */
        virtual unsigned int getNumberOfStates() const = 0;
        /**
         * Returns number of state for specified node.
         *
         * @param node Node to return state for
         *
         * @return Node state
         */
        // FIXME@avasyukov: we never use it. Is there any real use case?
        // If we remove it, the code will be much less confusing.
        // We can replace uint getNumberOfStates() with smth like bool shouldRecalcEachTime().
        virtual unsigned int getStateForNode(const CalcNode& node) const = 0;
        /**
         * Fills matrix \f$A_x\f$ using specified material parameters.
         *
         * @param a Matrix to fill
         * @param material Material to use
         * @param node Node to set matrix at
         */
        virtual void setX(GcmMatrix& a, const MaterialPtr& material, const CalcNode& node) = 0;
        /**
         * Fills matrix \f$A_y\f$ using specified material parameters.
         *
         * @param a Matrix to fill
         * @param material Material to use
         * @param node Node to set matrix at
         */
        virtual void setY(GcmMatrix& a, const MaterialPtr& material, const CalcNode& node) = 0;
        /**
         * Fills matrix \f$A_z\f$ using specified material parameters.
         *
         * @param a Matrix to fill
         * @param material Material to use
         * @param node Node to set matrix at
         */
        virtual void setZ(GcmMatrix& a, const MaterialPtr& material, const CalcNode& node) = 0;
        
    };

    typedef std::shared_ptr<RheologyMatrixSetter> SetterPtr;
    
    template<typename T, typename...Args>
    std::shared_ptr<T> makeSetterPtr(Args...args)
    {
        return std::make_shared<T>(args...);
    }
}
#endif /* RheologyMatrixSetter_HPP */
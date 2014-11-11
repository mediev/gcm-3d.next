#ifndef CALC_NODE_H_
#define CALC_NODE_H_

#include <vector>
#include <iostream>
#include <string>

#include "libgcm/node/Node.hpp"
#include "libgcm/util/Types.hpp"

#define VALUES_NUMBER 14


namespace gcm {

    /**
     * Calculation node implementaion. Contains all necessary information
     * about node used in computations.
     */
    class CalcNode : public Node {

    protected:
		// node material id
		uchar materialId;
		
		//	from Sasha: 
		//	We shouldn't keep main stress components in every node every time 
		//	but calculate them when necessary:
        //	delete mutable real mainStresses[3];

		//	from Sasha: 
		//	We shouldn't keep crack direction in every node every time,
		//	because it takes too many memory,
		//	but we can't calculate them when necessary
        //	TODO: How to delete it? 
        vector3r crackDirection;

        // rheology matrix
        RheologyMatrixPtr rheologyMatrix;

    public:

        union
        {
            real values[VALUES_NUMBER];

            struct
            {

                union
                {
                    real velocity[3];

                    struct
                    {
                        /**
                         * Velocity std::vector x component.
                         */
                        real vx;
                        /**
                         * Velocity std::vector y component.
                         */
                        real vy;
                        /**
                         * Velocity std::vector z component.
                         */
                        real vz;
                    };
                };

                union
                {
                    real stress[6];

                    struct
                    {
                        /**
                         * Stress tensor xx component.
                         */
                        real sxx;
                        /**
                         * Stress tensor xy component.
                         */
                        real sxy;
                        /**
                         * Stress tensor xz component.
                         */
                        real sxz;
                        /**
                         * Stress tensor yy component.
                         */
                        real syy;
                        /**
                         * Stress tensor yz component.
                         */
                        real syz;
                        /**
                         * Stress tensor zz component.
                         */
                        real szz;
                    };
                };
				/**
				 * Density
				 */
				real rho;
				/**
				 * Temperature	
				 */
				real T;
				/**
				 * Internal energy
				 */
				real U;
				/**
				 * Damage measure
				 */
				real damageMeasure;
				/**
				 * Another one damage measure, or plasticity measure, etc.
				 */
				real hi;
            };
        };

        /**
         * Default constructor. Constructs node with default parameters.
         */
        CalcNode();
        /**
         * Constructor. Creates node with specified number assigned.
         *
         * @param num Number of the node
         */
        CalcNode(int num);
        /**
         * Constructor. Creates node with specified number assigned and set
         * coordinates.
         *
         * @param num Number of the node
         * @param coords Node coords
         */
        CalcNode(int num, const vector3r& coords);
        /**
         * Constructor. Constructs copy of the passed object.
         *
         * @param src Calc node to make copy of.
         */
        CalcNode(const CalcNode& src);
        /**
         * Destructor.
         */
        ~CalcNode();

        /**
         * Assignment operator. Allows creation of calc node copy using
         * assignment statement.
         *
         * @param src Calc node to be copied.
         */
        CalcNode &operator=(const CalcNode &src);

        /**
         * Returns compression.
         *
         * @return Compression value.
         */
        real getCompression() const;
        /**
         * Returns compression.
         *
         * @return Compression value.
         */
        real getTension() const;
        /**
         * Returns shear.
         *
         * @return Shear value.
         */
        real getShear() const;
        /**
         * Returns deviator.
         *
         * @return Deviator value.
         */
        real getDeviator() const;
        /**
         * Returns pressure.
         *
         * @return Pressure value.
         */
        real getPressure() const;

        /**
         * Returns tensor J1 invariant. TODO document
         *
         * @return J1 value.
         */
        real getJ1() const;
        /**
         * Returns tensor J2 invariant. TODO document
         *
         * @return J2 value.
         */
        real getJ2() const;
        /**
         * Returns tensor J3 invariant. TODO document
         *
         * @return J3 value.
         */
        real getJ3() const;
        /**
		 * from Sasha: TODO delete it, because we shouldn't keep mainStressDirection
		 * at any node any time
         * TODO document.
         *
         * @param stress TODO document
         * @param std::vector TODO document
         */
        void calcMainStressDirectionByComponent(real stress, vector3r& vector) const;

        /**
         * Checks if rheology is valid. TODO document
         *
         * @return True in case rheology is valid and false otherwise.
         */
        bool rheologyIsValid() const;

        /**
         * Sets node material id.  Sets material id and updates values for
         * node material-related fields (e.g. rho)
         *
         * @param id Material id
         */
        void setMaterialId(uchar id);
        /**
         * Returns node material id.
         *
         * @return Material id.
         */
        uchar getMaterialId() const;
        /**
         * Returns node material.
         *
         * @return Material.
         */
        MaterialPtr getMaterial() const /*override*/;
        /**
         * Sets rheology matrix for node.
         */
        void setRheologyMatrix(RheologyMatrixPtr matrix);
        /**
         * Returns rheology matrix for node. It's wrapper for corresponding
         * material APIs.
         *
         * @return Rheology matrix.
         */
        RheologyMatrixPtr getRheologyMatrix() const;
        /**
         * Sets density value for node.
         *
         * @param rho Density value
         */
        void setRho(real rho);
        /**
         * Returns density value for node.
         * @return Density value.
         */
        real getRho() const override;
        /**
         * Returns crack direction. TODO document
         *
         * @return Crack direction.
         */
        const vector3r& getCrackDirection() const;
        /**
         * Creates crack in specified direction. TODO document
         *
         * @param direction Crack direction.
         */
        void createCrack(int direction);
        /**
         * Creates crack in specified direction. TODO document
         *
         * @param direction Crack direction.
         */
        void createCrack(const vector3r& crack);
		/**
		 * TODO document
		 *
		 * @param TODO document
		 */
        void createCrack(real x, real y, real z);
        /**
         * TODO document
         *
         * @param TODO document
         */
        void exciseByCrack();
		/**
		 * TODO document
		 *
		 * @param TODO document
		 */
        void cleanStressByDirection(const vector3r& direction);
		/**
		 * Sets damage measure value for node.
		 *
		 * @param value damage measure value
		 */
        void setDamageMeasure(real value);
		/**
		 * Returns damage measure for node.
		 * @return Damage measure value.
		 */
        real getDamageMeasure() const;
		/**
		 *	Calculates main stress components
		 *
		 */
		vector3r calcMainStressComponents() const;
    };
}

namespace std {

    inline std::ostream& operator<<(std::ostream &os, const gcm::CalcNode &node) {
        os << "\n\tCalcNode number: " << node.number << "\n";
        os << "\tCoords:";
        for (int i = 0; i < 3; i++)
            os << " " << node.coords[i];
        os << "\n\tVelocity:";
        for (int i = 0; i < 3; i++)
            os << " " << node.values[i];
        os << "\n\tStress:";
        for (int i = 3; i < VALUES_NUMBER; i++)
            os << " " << node.values[i];
        os << "\n\tRho: " << node.getRho();
        os << "\n\tIsBorder: " << node.isBorder();
        return os;
    }
}

#endif

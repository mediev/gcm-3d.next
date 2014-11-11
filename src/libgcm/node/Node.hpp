#ifndef GCM_NODE_H_
#define GCM_NODE_H_

#include "libgcm/util/Types.hpp"

namespace gcm {

    /**
     * Base class that contains node data. All other node implementations
     * should derive from this one. Contains basic node information such
     * as number and coordinates.
     *
     */
    class Node {
	protected:
		//  public flags container type

		typedef union {
			uchar flags;

			struct {
				uchar contact : 1;
				uchar order : 1;
				uchar isDestroyed : 1;
				uchar isContactDestroyed : 1;
				uchar flag1 : 1;
				uchar flag2 : 1;
				uchar flag3 : 1;
				uchar flag4 : 1;
			};
		} PublicFlags;

		// private flags container

		typedef union {
			uchar flags;

			struct {
				uchar local : 1;
				uchar used : 1;
				uchar border : 1;
				//	from Sasha:	After deleting mainStresses[3] it's not necessary:
				//	delete	mutable uchar mainStressCalculated : 1;
			};
		} PrivateFlags;

		// error flags container type

		typedef union {
			uchar flags;

			struct {
				uchar xNeigh : 1;
				uchar yNeigh : 1;
				uchar zNeigh : 1;
				uchar outerNormal : 1;
			};
		} ErrorFlags;

		// Node public flags. These flags are to synchrinized using MPI.
		PublicFlags publicFlags;
		// Node private flags. Intended to be for internal use only.
		PrivateFlags privateFlags;
		// Node flags to indicate different issues with this node during calculations
		ErrorFlags errorFlags;

		// border and contac conditions
		// FIXME should these fields be protected?
		uchar borderConditionId;
		uchar contactConditionId;
		
		// sets private flags
		void setPrivateFlags(uchar flags);
		// sets public flags
		void setPublicFlags(uchar flags);
		// sets error flags
		void setErrorFlags(uchar flags);
		
    public:
        /**
         * Number of the node.
         */
        int number;
        /**
         * Node coords.
         */
        vector3r coords;
        /**
         * Default node constructor. Creates new node with all members
         * set to default values;
         */
        Node();
        /**
         * Copy constructor
         */
        Node(const Node& src);
        /**
         * Constructor. Creates node with specified number assigned.
         *
         * @param num Number of the node
         */
        Node(int num);
        /**
         * Constructor. Creates node with specified number assigned
         * and set coordinates.
         *
         * @param num Number of the node
         * @param coords Node coords
         */
        Node(int num, const vector3r& coords);
        /**
         * Destructor
         */
        virtual ~Node() = 0;

		/**
		 * Number of pair node in contact. FIXME
		 */
		int contactNodeNum;
		/**
		 * Contact direction. FIXME
		 */
		uchar contactDirection;
		/**
		 * Identifier of the body this node belongs to.
		 */
		uchar bodyId;

		/**
		 * Clears flags state. Drops main stresses and error flags.
		 */
		void clearState();
		/**
		 * Clears error flags.
		 */
		void clearErrorFlags();

		/**
		 * Indicates whether node is in contact or not.
		 *
		 * @return True in case of contact and false otherwise.
		 */
		bool isInContact() const;
		/**
		 * Sets new contact state of the node
		 *
		 * @param value Contact state.
		 */
		void setInContact(bool value);

		/**
		 * Indicates whether node is in destroyed area
		 *
		 * @return True in case of node belonging to destroyed area
		 */
		bool isDestroyed() const;
		/**
		 * Sets new destroyed state of the node
		 *
		 * @param value Destroyed state.
		 */
		void setDestroyed(bool value);

		/**
		 * Indicates whether node is on destroyed contact
		 *
		 * @return True in case of destroyed contact and false otherwise.
		 */
		bool isContactDestroyed() const;
		/**
		 * Sets new contact destoyed state of the node
		 *
		 * @param value Contact destoyed state.
		 */
		void setContactDestroyed(bool value);

		/**
		 * Indicates whether node is local or not.
		 *
		 * @return True in case of local node and false otherwise.
		 */
		bool isLocal(bool mustBeUsed = true) const;
		/**
		 * Indicates whether node is remote or not.
		 *
		 * @return True in case of remote node and false otherwise.
		 */
		bool isRemote() const;

		/**
		 * Sets node placement to specified value and also marks node as used
		 *
		 * @param Flag that indicates whether node is local or not
		 */
		void setPlacement(bool local);

		/**
		 * Indicates whether node is used or not.
		 *
		 * @return True in case of used node and false otherwise.
		 */
		bool isUsed() const;
		/**
		 * Sets node used flag.
		 *
		 * @param value Used flag value
		 */
		void setUsed(bool value);

		/**
		 * Indicates whether node is first order or not.
		 *
		 * @return True in case of first order node and false otherwise.
		 */
		bool isFirstOrder() const;
		/**
		 * Indicates whether node is second order or not.
		 *
		 * @return True in case of second order node and false otherwise.
		 */
		bool isSecondOrder() const;
		/**
		 * Sets node order flag.
		 *
		 * @param order Node order
		 */
		void setOrder(uchar order);

		/**
		 * Returns whether node is border or not.
		 *
		 * @return True in case of border node and false otherwise.
		 */
		bool isBorder() const;
		/**
		 * Returns whether node is inner or not.
		 *
		 * @return True in case of inner node and false otherwise.
		 */
		bool isInner() const;
		/**
		 * Sets node border flag.
		 *
		 * @param value  Border flag value.
		 */
		void setIsBorder(bool value);

		/**
		 * Sets node xneigh error flag. TODO document
		 */
		void setXNeighError();
		/**
		 * Sets node yneigh error flag. TODO document
		 */
		void setYNeighError();
		/**
		 * Sets node zneigh error flag. TODO document
		 */
		void setZNeighError();
		/**
		 * Sets node outer normal error flag. TODO document
		 */
		void setNormalError();
		/**
		 * Sets node neigh error flag depending on specified axis. TODO document
		 *
		 * @param axisName Number of axis to set error flag for.
		 */
		void setNeighError(unsigned int axisNum);

		/**
		 * Returns value of specified custom flag.
		 *
		 * @param flag Flag to get value of.
		 * @return Flag state.
		 */
		bool getCustomFlag(uchar flag) const;
		/**
		 * Sets value of custom flag.
		 *
		 * @param flag Flag to set value of.
		 * @param value New flag value
		 */
		void setCustomFlag(uchar flag, bool value);
		/**
		 * Returns private flags for node.
		 *
		 * @return Private flags
		 */
		uchar getPrivateFlags() const;
		/**
		 * Returns public flags for node.
		 *
		 * @return Public flags
		 */
		uchar getPublicFlags() const;
		/**
		 * Returns error flags for node.
		 *
		 * @return Error flags
		 */
		uchar getErrorFlags() const;
		/**
		 * Sets border condition id. TODO document
		 *
		 * @param  newBorderConditionId Id of the new border condition.
		 */
		void setBorderConditionId(uchar newBorderConditionId);
		/**
		 * Returns id of the node border condition. TODO document
		 *
		 * @return Id of the border condition.
		 */
		uchar getBorderConditionId() const;

		/**
		 * Sets contact condition id. TODO document
		 *
		 * @param  newContactConditionId Id of the new contact condition.
		 */
		void setContactConditionId(uchar newContactConditionId);
		/**
		 * Returns id of the node contact condition. TODO document
		 *
		 * @return Id of the contact condition.
		 */
		uchar getContactConditionId() const;
		/**
		 * Constant to access custom flag1 using getCustomFlag / setCustomFlag.
		 */
		static const uchar FLAG_1 = 1;
		/**
		 * Constant to access custom flag2 using getCustomFlag / setCustomFlag.
		 */
		static const uchar FLAG_2 = 2;
		/**
		 * Constant to access custom flag3 using getCustomFlag / setCustomFlag.
		 */
		static const uchar FLAG_3 = 3;
		/**
		 * Constant to access custom flag4 using getCustomFlag / setCustomFlag.
		 */
		static const uchar FLAG_4 = 4;
    };
}

#endif

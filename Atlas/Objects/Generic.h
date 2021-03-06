// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright 2000-2001 Stefanus Du Toit and Aloril.
// Copyright 2001-2005 Alistair Riddoch.
// Automatically generated using gen_cpp.py.

#ifndef ATLAS_OBJECTS_OPERATION_GENERIC_H
#define ATLAS_OBJECTS_OPERATION_GENERIC_H

#include <Atlas/Objects/RootOperation.h>
#include <Atlas/Objects/SmartPtr.h>

namespace Atlas { namespace Objects { namespace Operation { 

/** Base operation for all operators

This is base operation for all other
    operations and defines basic attributes. You can use this as
    starting point for browsing whole operation hiearchy. refno refers
    to operation this is reply for. In examples all attributes that
    are just as examples (and thus world specific) are started with 'e_'.

*/

class GenericData;
typedef SmartPtr<GenericData> Generic;

static const int GENERIC_NO = 41;

/// \brief Base operation for all operators.
///
/** This is base operation for all other
    operations and defines basic attributes. You can use this as
    starting point for browsing whole operation hiearchy. refno refers
    to operation this is reply for. In examples all attributes that
    are just as examples (and thus world specific) are started with 'e_'.
 */
class GenericData : public RootOperationData
{
protected:
    /// Construct a GenericData class definition.
    GenericData(GenericData *defaults = NULL) : 
        RootOperationData((RootOperationData*)defaults)
    {
        m_class_no = GENERIC_NO;
    }
    /// Default destructor.
    virtual ~GenericData();

public:
    /// Set the type of this object.
    void setType(const std::string &, int);

    /// Copy this object.
    virtual GenericData * copy() const;

    /// Is this instance of some class?
    virtual bool instanceOf(int classNo) const;


    virtual void iterate(int& current_class, std::string& attr) const
        {if(current_class == GENERIC_NO) current_class = -1; RootOperationData::iterate(current_class, attr);}

    //freelist related things
public:
    static GenericData *alloc();
    virtual void free();

    /// \brief Get the reference object that contains the default values for
    /// attributes of instances of the same class as this object.
    ///
    /// @return a pointer to the default object.
    virtual GenericData *getDefaultObject();

    /// \brief Get the reference object that contains the default values for
    /// attributes of instances of this class.
    ///
    /// @return a pointer to the default object.
    static GenericData *getDefaultObjectInstance();
private:
    static GenericData *defaults_GenericData;
    static GenericData *begin_GenericData;
};

} } } // namespace Atlas::Objects::Operation

#endif // ATLAS_OBJECTS_OPERATION_GENERIC_H

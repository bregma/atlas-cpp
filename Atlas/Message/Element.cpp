// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2001 Stefanus Du Toit, Karsten-O. Laux

// $Id$

#include <Atlas/Message/Element.h>

namespace Atlas { namespace Message {

void Element::clear(Type new_type)
{
  switch(t) 
     {
   case TYPE_NONE:
   case TYPE_INT:
   case TYPE_FLOAT:
   case TYPE_PTR:
     break;
   case TYPE_STRING:
     s->unref();
     break;
   case TYPE_MAP:
     m->unref();
     break;
   case TYPE_LIST:
     l->unref();
     break;
   }
  
  t = new_type;
}

Element::Element(const Element& obj) : t(obj.t)
{
  switch(t) 
    {
      case TYPE_NONE:
        break;
      case TYPE_INT:
        i = obj.i;
        break;
      case TYPE_FLOAT:
        f = obj.f;
        break;
      case TYPE_PTR:
        p = obj.p;
        break;
      case TYPE_STRING:
        s = obj.s;
        s->ref();
        break;
      case TYPE_MAP:
        m = obj.m;
        m->ref();
        break;
      case TYPE_LIST:
        l = obj.l;
        l->ref();
        break;
    }
        
}

Element& Element::operator=(const Element& obj) 
{
  //check for self assignment
  if(&obj == this)
    return *this;

  //first clear
  clear(obj.t);

  // then perform actual assignment of members
  switch(t) 
    {
    case TYPE_NONE:
      break;
    case TYPE_INT:
      i = obj.i;
      break;
    case TYPE_FLOAT:
      f = obj.f;
      break;
    case TYPE_PTR:
      p = obj.p;
      break;
    case TYPE_STRING:
      s = obj.s;
      s->ref();
      break;
    case TYPE_MAP:
      m = obj.m;
      m->ref();
      break;
    case TYPE_LIST:
      l = obj.l;
      l->ref();
      break;
    }

  return *this;
}

bool Element::operator==(const Element& o) const
{
    if (t != o.t) { return false; }
    switch(t) {
        case TYPE_NONE: return true;
        case TYPE_INT: return i == o.i;
        case TYPE_FLOAT: return f == o.f;
        case TYPE_PTR: return p == o.p;
        case TYPE_STRING: return *s == *o.s;
        case TYPE_MAP: return *m == *o.m;
        case TYPE_LIST: return *l == *o.l;
    }
    return false;
}

const char * Element::typeName(Type ot)
{
    switch (ot) {
        case TYPE_NONE: return "none";
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_PTR: return "pointer";
        case TYPE_STRING: return "string";
        case TYPE_MAP: return "map";
        case TYPE_LIST: return "list";
    }
    return "UNKNOWN";
}

} } //namespace Atlas::Message


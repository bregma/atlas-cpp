// This file may be redistributed and modified under the terms of the
// GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Michael Day

#include "../Stream/Codec.h"

using namespace std;
using namespace Atlas::Stream;

class XML : public Codec
{
    public:

    XML(iostream&, Filter*, Bridge*);

    virtual void Initialise(iostream&, Filter*, Bridge*);

    virtual void MessageBegin();
    virtual void MessageMapBegin();
    virtual void MessageEnd();
    
    virtual void MapItem(const std::string& name, const Map&);
    virtual void MapItem(const std::string& name, const List&);
    virtual void MapItem(const std::string& name, int);
    virtual void MapItem(const std::string& name, float);
    virtual void MapItem(const std::string& name, const std::string&);
    virtual void MapItem(const std::string& name, const Atlas::Object&);
    virtual void MapEnd();
    
    virtual void ListItem(const Map&);
    virtual void ListItem(const List&);
    virtual void ListItem(int);
    virtual void ListItem(float);
    virtual void ListItem(const std::string&);
    virtual void ListItem(const Atlas::Object&);
    virtual void ListEnd();

    protected:

    iostream& socket;
    Filter* filter;
    Bridge* bridge;
};

namespace
{
    Codec::Factory<XML> factory("XML", Codec::Metrics(1, 2));
}
    
XML::XML(iostream& socket, Filter* f, Bridge* b) : socket(socket)
{
    filter = f;
    bridge = b;
}

void XML::MessageBegin()
{
    socket << "<obj>";
}

void XML::MessageMapBegin()
{
}

void XML::MessageEnd()
{
    socket << "</obj>";
}

void XML::MapItem(const std::string& name, const Map&)
{
    socket << "<map name=\"" << name << "\">";
}

void XML::MapItem(const std::string& name, const List&)
{
    socket << "<list name=\"" << name << "\">";
}

void XML::MapItem(const std::string& name, int data)
{
    socket << "<int name=\"" << name << "\">" << data << "</int>";
}

void XML::MapItem(const std::string& name, float data)
{
    socket << "<float name=\"" << name << "\">" << data << "</float>";
}

void XML::MapItem(const std::string& name, const std::string& data)
{
    socket << "<string name=\"" << name << "\">" << data << "</string>";
}

void XML::MapItem(const std::string& name, const Atlas::Object& data)
{
    // FIXME recurse through object and send it
}

void XML::MapEnd()
{
    socket << "</map>";
}

void XML::ListItem(const Map&)
{
    socket << "<map>";
}

void XML::ListItem(const List&)
{
    socket << "<list>";
}

void XML::ListItem(int data)
{
    socket << "<int>" << data << "</int>";
}

void XML::ListItem(float data)
{
    socket << "<float>" << data << "</float>";
}

void XML::ListItem(const std::string& data)
{
    socket << "<string>" << data << "</string>";
}

void XML::ListItem(const Atlas::Object& data)
{
    // FIXME recurse through object and send it
}

void XML::ListEnd()
{
    socket << "</list>";
}


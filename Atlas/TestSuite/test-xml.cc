// This file may be redistributed and modified under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Michael Day

#include "../Codec.h"
#include "../Hack.h"
#include "../Funky/Encoder.h"

#include <iostream>

using namespace std;
using namespace Atlas;

class loopbuf : public streambuf
{
    public:

    loopbuf(string &write, string &read) : write(write), read(read) { }

    virtual int overflow(int c)
    {
	write += c;
	return c;
    }
    
    virtual int uflow()
    {
	int c = read[0];
	read.erase(read.begin());
	return c;
    }
    
    virtual int pbackfail(int c)
    {
	string temp;
	temp += c;
	temp += read;
	read = temp;
	return c;
    }

    virtual int showmanyc()
    {
	return read.size();
    }
    
    private:

    string& write;
    string& read;
};

class LoopBridge : public Bridge
{
    public:

    virtual void StreamBegin()
    {
	cout << "StreamBegin!\n";
    }

    virtual void StreamEnd()
    {
        cout << "StreamEnd!\n";
    }

    virtual void MessageBegin()
    {
	cout << "MessageBegin\n";
    }
    
    virtual void MessageItem(const Map&)
    {
	cout << "MessageItemMap\n";
    }
    
    virtual void MessageEnd()
    {
	cout << "MessageEnd\n";
    }
    
    // Interface for map context

    virtual void MapItem(const std::string& name, const Map&)
    {
	cout << name << ":MapItemMap\n";
    }
    
    virtual void MapItem(const std::string& name, const List&)
    {
	cout << name << ":MapItemList\n";
    }
    
    virtual void MapItem(const std::string& name, int data)
    {
	cout << name << ':' << data << '\n';
    }
    
    virtual void MapItem(const std::string& name, double data)
    {
	cout << name << ':' << data << '\n';
    }
    
    virtual void MapItem(const std::string& name, const std::string& data)
    {
	cout << name << ':' << data << '\n';
    }
    
    virtual void MapEnd()
    {
	cout << "MapEnd\n";
    }
    
    // Interface for list context
    
    virtual void ListItem(const Map&)
    {
	cout << "ListItemMap\n";
    }
    
    virtual void ListItem(const List&)
    {
	cout << "ListItemList\n";
    }
    
    virtual void ListItem(int data)
    {
	cout << data << '\n';
    }
    
    virtual void ListItem(double data)
    {
	cout << data << '\n';
    }
    
    virtual void ListItem(const std::string& data)
    {
	cout << data << '\n';
    }
    
    virtual void ListEnd()
    {
	cout << "ListEnd\n";
    }
    
};

int main()
{
    string client_buffer;
    string server_buffer = "<atlas><obj><map><int name=\"id\">17</int><string name=\"name\">Fred (the + great)</string><float name=\"weight\">1.5</float></map></obj></atlas>";
    loopbuf serverbuf(server_buffer, client_buffer);
    loopbuf clientbuf(client_buffer, server_buffer);    
    iostream client_stream(&clientbuf);
    iostream server_stream(&serverbuf);

    LoopBridge bridge;
    
    Codec<iostream>* codec = Atlas::UngodlyHack::GetXML(client_stream, &bridge);

    Funky::Encoder enc = Funky::Encoder(codec);

    enc << Funky::Encoder::begin_message
          << Funky::Encoder::begin_map
              << make_pair((string)"id", 17)
              << make_pair((string)"name", (string)"Fred (the + great)")
              << make_pair((string)"weight", 1.5)
          << Funky::Encoder::end_map
          << Funky::Encoder::end_message;

    /*
    codec->MessageBegin();
    codec->MessageItem(Codec<iostream>::MapBegin);
	codec->MapItem("id", 17);
	codec->MapItem("name", "Fred (the + great)");
	codec->MapItem("weight", 1.5);
	codec->MapEnd();
    codec->MessageEnd();
    */
    
    codec->Poll();

    cout << client_buffer << endl;
    cout << server_buffer << endl;
    
          
/*    

    Negotiate s("SERVER BOB", server_stream);
    Negotiate c("CLIENT 1.0", client_stream);

  //while(!s.Done() && !c.Done())
  for(int i=0; i < 10; i++)
    {
      //cout << "SB : " << server_buf.size() << " [" << server_buf << "] "
      //   << "CB : " << client_buf.size() << " [" << client_buf << "] " 
      //   <<endl;
      s.negotiateServer();
      c.negotiateClient();
      if(s.done() && c.done()) break;
    }

  if(!s.done()) cout << "Server NOT done" << endl;
  if(!c.done()) cout << "Client NOT done" << endl;
*/
    return 0;
}

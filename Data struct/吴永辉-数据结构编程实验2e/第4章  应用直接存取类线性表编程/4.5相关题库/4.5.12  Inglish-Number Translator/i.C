#include <string>
#include <stack>
#include <map>

struct COperation
{
 virtual int number( int num, int b)
 { return num;}
 virtual int base( int b)
 { return b;}
};

struct CAddOp : public COperation
{
 int _toAdd;
 CAddOp( int toAdd)
  :_toAdd(toAdd) {};
 virtual int number( int num, int b)
 { return num+b*_toAdd;}

};

struct CNegOp : public COperation
{
 CNegOp()
 {}
 virtual int number( int num, int b)
 { return -num;}

};

struct CBaseMOp : public COperation
{
 int _baseM;
CBaseMOp( int baseM)
 : _baseM( baseM) {}
 virtual int base( int b)
 { return b*_baseM;}
};

struct CBaseOp : public COperation
{
 int _base;
CBaseOp( int base)
 : _base( base) {}
 virtual int base( int b)
 { return _base;}
};


struct COperations
{
 std::map< std::string, COperation*>  _o;

 COperations()
 {
  _o["negative"] = new CNegOp();
  _o["zero"]     = new CAddOp(0);
  _o["one"]      = new CAddOp(1);
  _o["two"]      = new CAddOp(2);
  _o["three"]    = new CAddOp(3);
  _o["four"]     = new CAddOp(4);
  _o["five"]     = new CAddOp(5);
  _o["six"]      = new CAddOp(6);
  _o["seven"]    = new CAddOp(7);
  _o["eight"]    = new CAddOp(8);
  _o["nine"]     = new CAddOp(9);
  _o["ten"]      = new CAddOp(10);
  _o["eleven"]   = new CAddOp(11);
  _o["twelve"]   = new CAddOp(12);
  _o["thirteen"] = new CAddOp(13);
  _o["fourteen"] = new CAddOp(14);
  _o["fifteen"]  = new CAddOp(15);
  _o["sixteen"]  = new CAddOp(16);
  _o["seventeen"]= new CAddOp(17);
  _o["eighteen"] = new CAddOp(18);
  _o["nineteen"] = new CAddOp(19);
  _o["twenty"]   = new CAddOp(20);
  _o["thirty"]   = new CAddOp(30);
  _o["forty"]    = new CAddOp(40);
  _o["fifty"]    = new CAddOp(50);
  _o["sixty"]    = new CAddOp(60);
  _o["seventy"]  = new CAddOp(70);
  _o["eighty"]   = new CAddOp(80);
  _o["ninety"]   = new CAddOp(90);
  
  _o["hundred"]  = new CBaseMOp(100);
  _o["thousand"] = new CBaseOp(1000);
  _o["million"]  = new CBaseOp( 1000000);
 }

 ~COperations()
 {
  for( std::map< std::string, COperation*>::iterator it=_o.begin(); it!=_o.end();++it)
   delete it->second;
 }
}_OPS;
 



#include <iostream>


int translate(std::stack<std::string>& sstack)
{
 int num = 0;
 int b = 1;

 while(!sstack.empty())
 {
  COperation* op = _OPS._o[sstack.top()];
  sstack.pop();
  num = op->number( num, b);
  b   = op->base( b);
 }
 return num;
}

int main ()
{

 std::stack<std::string> sstack;
 while( true)
 {
  std::string s;
  char c;
  std::cin >> c;
  while((c>='a')&&(c<='z'))
  {
   s += c;
   c = std::cin.get();
  }
  if(!s.empty())
   sstack.push(s);
  
  if(c=='\n')
   if( sstack.empty())
    break;
   else
    std::cout << translate( sstack) << std::endl;

 } 
 return 0;
}

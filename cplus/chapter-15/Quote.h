#ifndef _QUOTE_H
#define _QUOTE_H
#include <iostream>
#include <string>
class Quote
{
	public:
		Quote()=default;
		Quote(const std::string &book,double sales_price):price(sales_price),bookNo(book) {}
		std::string isbn() const {return bookNo;}
		virtual double net_price(std::size_t n) const {return n*price;}
		virtual std::string debug() const {return "bookNo="+bookNo+"\n"+"price="+std::to_string(price);}
		virtual ~Quote()=default;
	protected:
		double price=0.0;
	private:
		std::string bookNo;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n);
class Bulk_quote:public Quote
{
	public:
		Bulk_quote()=default;
		Bulk_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),min_qty(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n>=min_qty)
				return n*(1-discount)*price;
			else
				return n*price;
		}
		virtual std::string debug() const
		{
			return Quote::debug()+"\n"+"min_qty="+std::to_string(min_qty)+"\n"+"discount="+std::to_string(discount);
		}
	private:
		std::size_t min_qty=0;
		double discount=0.0;
};


class Limit_quote:public Quote
{
	public:
		Limit_quote()=default;
		Limit_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),max_qty(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n<=max_qty)
				return n*(1-discount)*price;
			else
				return max_qty*(1-discount)*price+(n-max_qty)*price;
		}
		virtual std::string debug() const
		{
			return Quote::debug()+"\n"+"max_qty="+std::to_string(max_qty)+"\n"+"discount="+std::to_string(discount);
		}
	private:
		std::size_t max_qty=0;
		double discount=0.0;
};
#endif

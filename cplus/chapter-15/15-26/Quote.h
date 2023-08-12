#ifndef _QUOTE_H
#define _QUOTE_H
#include <iostream>
#include <string>
class Quote
{
	public:
		Quote()=default;
		Quote(const Quote &rhs):price(rhs.price),bookNo(rhs.bookNo) {std::cout<<"Quote copy constructor"<<std::endl;}
		Quote(Quote &&rhs) noexcept :price(rhs.price),bookNo(std::move(rhs.bookNo)) {std::cout<<"Quote move constructor"<<std::endl;}
		Quote & operator=(const Quote &rhs)
		{
			std::cout<<"Quote copy assignment operator"<<std::endl;
			price=rhs.price;
			bookNo=rhs.bookNo;
			return *this;
		}
		Quote & operator=(Quote &&rhs) noexcept
		{
			std::cout<<"Quote move assignment operator"<<std::endl;
			if(this!=&rhs)
			{
				price=rhs.price;
				bookNo=std::move(rhs.bookNo);
			}
			return *this;
		}
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
		Bulk_quote(const Bulk_quote &rhs):Quote(rhs),min_qty(rhs.min_qty),discount(rhs.discount) {std::cout<<"Bulk_quote copy constructor"<<std::endl;}
		Bulk_quote(Bulk_quote &&rhs) noexcept : Quote(std::move(rhs)),min_qty(rhs.min_qty),discount(rhs.discount) {std::cout<<"Bulk_quote move constructor"<<std::endl;}
		Bulk_quote & operator=(const Bulk_quote &rhs)
		{
			std::cout<<"Bulk_quote copy assignment operator"<<std::endl;
			Quote::operator=(rhs);
			min_qty=rhs.min_qty;
			discount=rhs.discount;
			return *this;
		}
		Bulk_quote & operator=(Bulk_quote &&rhs) noexcept
		{
			std::cout<<"Bulk_quote move assignment operator"<<std::endl;
			if(this!=&rhs)
			{
				Quote::operator=(std::move(rhs));
				min_qty=rhs.min_qty;
				discount=rhs.discount;
			}
			return *this;
		}
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
#endif

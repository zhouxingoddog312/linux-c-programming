#ifndef _QUOTE_H
#define _QUOTE_H
#include <set>
#include <iostream>
#include <string>
#include <memory>
class Quote
{
	public:
		Quote()=default;
		Quote(const std::string &book,double sales_price):price(sales_price),bookNo(book) {}
		std::string isbn() const {return bookNo;}
		virtual double net_price(std::size_t n) const {return n*price;}
		virtual std::string debug() const {return "bookNo="+bookNo+"\n"+"price="+std::to_string(price);}
		virtual Quote * clone() const & {return new Quote(*this);}
		virtual Quote * clone() && {return new Quote(std::move(*this));}
		virtual ~Quote()=default;
	protected:
		double price=0.0;
	private:
		std::string bookNo;
};
class Disc_quote:public Quote
{
	public:
		Disc_quote()=default;
		Disc_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),quantity(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const=0;
		virtual std::string debug() const override
		{
			return Quote::debug()+"\n"+"quantity="+std::to_string(quantity)+"\n"+"discount="+std::to_string(discount);
		}
	protected:
		std::size_t quantity=0;
		double discount=0.0;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n);
class Bulk_quote:public Disc_quote
{
	public:
		Bulk_quote()=default;
		Bulk_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Disc_quote(book,sales_price,qty,disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n>=quantity)
				return n*(1-discount)*price;
			else
				return n*price;
		}
		Bulk_quote * clone() const & {return new Bulk_quote(*this);}
		Bulk_quote * clone() && {return new Bulk_quote(std::move(*this));}
};
class Limit_quote:public Disc_quote
{
	public:
		Limit_quote()=default;
		Limit_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Disc_quote(book,sales_price,qty,disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n<=quantity)
				return n*(1-discount)*price;
			else
				return quantity*(1-discount)*price+(n-quantity)*price;
		}
};
class basket
{
	public:
		void add_item(const Quote &sale) {items.insert(std::shared_ptr<Quote>(sale.clone()));}
		void add_item(Quote &&sale) {items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));}
		double total_receipt(std::ostream &os) const
		{
			double sum=0.0;
			for(std::multiset<std::shared_ptr<Quote>,decltype(compare) *>::const_iterator iter=items.cbegin();iter!=items.cend();iter=items.upper_bound(*iter))
				sum+=print_total(os,**iter,items.count(*iter));
			os<<"Total Sale: "<<sum<<std::endl;
			return sum;
		}
	private:
		static bool compare(const std::shared_ptr<Quote> &,const std::shared_ptr<Quote> &);
		std::multiset<std::shared_ptr<Quote>,decltype(compare) *> items{compare};
};
#endif

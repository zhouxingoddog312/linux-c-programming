#ifndef _QUERY_H
#define _QUERY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
class QueryResult;
class TextQuery
{
	public:
		using line_no=std::vector<std::string>::size_type;
		TextQuery(std::ifstream &);
		QueryResult query(const std::string &) const;
	private:
		std::shared_ptr<std::vector<std::string>> file;
		std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};
class QueryResult
{
	friend std::ostream &print(std::ostream &,const QueryResult &);
	public:
		QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<std::vector<std::string>> f):sought(s),lines(l),file(f){}
		std::set<std::vector<std::string>::size_type>::iterator begin() const {return lines->begin();}
		std::set<std::vector<std::string>::size_type>::iterator end() const {return lines->end();}
		std::shared_ptr<std::vector<std::string>> get_file(){return file;}
	private:
		std::string sought;
		std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
		std::shared_ptr<std::vector<std::string>> file;
};
std::ostream &print(std::ostream &,const QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
}
class Query_base
{
	friend class Query;
	protected:
		using line_no=TextQuery::line_no;
		virtual ~Query_base()=default;
	private:
		virtual QueryResult eval(const TextQuery &) const=0;
		virtual std::string rep() const=0;
};
class Query
{
	friend Query operator~(const Query &);
	friend Query operator&(const Query &,const Query &);
	friend Query operator|(const Query &,const Query &);
	public:
		Query(const std::string &);
		
		Query(const Query &rhs):q(rhs.q),reference_count(rhs.reference_count) {++*reference_count;}
		Query & operator=(const Query &);
		~Query();

		QueryResult eval(const TextQuery &t) const {return q->eval(t);}
		std::string rep() const {return q->rep();}
	private:
		Query(Query_base *query):q(query),reference_count(new std::size_t(1)) {}
		Query_base *q;
		std::size_t *reference_count;
};
class WordQuery:public Query_base
{
	friend class Query;
	private:
		WordQuery(const std::string &s):query_word(s) {}
		virtual QueryResult eval(const TextQuery &t) const {return t.query(query_word);}
		virtual std::string rep() const {return query_word;}
		std::string query_word;
};

inline Query::Query(const std::string &s):q(new WordQuery(s)),reference_count(new std::size_t(1)) {}

class NotQuery:public Query_base
{
	friend Query operator~(const Query &);
	private:
		NotQuery(const Query &q):query(q) {}
		virtual QueryResult eval(const TextQuery &) const;
		virtual std::string rep() const {return "~("+query.rep()+")";}
		Query query;
};
inline Query operator~(const Query &q) {return new NotQuery(q);}
class BinaryQuery:public Query_base
{
	protected:
		BinaryQuery(const Query &left,const Query &right,const std::string &s):lhs(left),rhs(right),opSym(s) {}
		virtual std::string rep() const {return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";}
		Query lhs,rhs;
		std::string opSym;
};
class AndQuery:public BinaryQuery
{
	friend Query operator&(const Query&,const Query&);
	private:
		AndQuery(const Query &left,const Query &right):BinaryQuery(left,right,"&") {}
		virtual QueryResult eval(const TextQuery &) const;
};
inline Query operator&(const Query &left,const Query &right) {return new AndQuery(left,right);}
class OrQuery:public BinaryQuery
{
	friend Query operator|(const Query &,const Query &);
	private:
		OrQuery(const Query &left,const Query &right):BinaryQuery(left,right,"|") {}
		virtual QueryResult eval(const TextQuery &) const;
};
inline Query operator|(const Query &left,const Query &right) {return new OrQuery(left,right);}
inline std::ostream & operator<<(std::ostream &os,const Query &q) {return os<<q.rep();}
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 18:51:21 by tdemay            #+#    #+#             */
/*   Updated: 2015/06/08 14:34:46 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calculator.hpp"

Calculator::Calculator( void ) {
	this->_stack = new std::vector<IOperand const*>();
	this->_script = new std::vector<std::string>();
	this->_error = new std::vector<std::string>();
	this->_count_line = 0;
	this->_eCreate[Int8] = &Calculator::createInt8;
	this->_eCreate[Int16] = &Calculator::createInt16;
	this->_eCreate[Int32] = &Calculator::createInt32;
	this->_eCreate[Float] = &Calculator::createFloat;
	this->_eCreate[Double] = &Calculator::createDouble;

	this->_eOpArg.insert(std::make_pair("push", &Calculator::push));
	this->_eOpArg.insert(std::make_pair("assert", &Calculator::assert));

	this->_eOp.insert(std::make_pair("pop", &Calculator::pop));
	this->_eOp.insert(std::make_pair("dump", &Calculator::dump));
	this->_eOp.insert(std::make_pair("add", &Calculator::add));
	this->_eOp.insert(std::make_pair("sub", &Calculator::sub));
	this->_eOp.insert(std::make_pair("mul", &Calculator::mul));
	this->_eOp.insert(std::make_pair("div", &Calculator::div));
	this->_eOp.insert(std::make_pair("mod", &Calculator::mod));
	this->_eOp.insert(std::make_pair("print", &Calculator::print));

	this->_type = new std::map<std::string, eOperandType>();
	this->_type->insert(std::make_pair("int8", Int8));
	this->_type->insert(std::make_pair("int16", Int16));
	this->_type->insert(std::make_pair("int32", Int32));
	this->_type->insert(std::make_pair("float", Float));
	this->_type->insert(std::make_pair("double", Double));
	return;
}

Calculator::~Calculator( void ) {
	delete	this->_stack;
	delete	this->_script;
	delete	this->_error;
	delete	this->_type;
	return;
}

/*
**  Creation Member
*/

IOperand const *	Calculator::createOperand( eOperandType type, std::string const & value ) const {
	MFP		pf = this->_eCreate[type];
	return (this->*pf)(value);
}

IOperand const *	Calculator::createInt8( std::string const & value ) const {
//	std::cout << "create int8(" << value << ")" << std::endl;
	return (new Int8_t(this, value));
}

IOperand const *	Calculator::createInt16( std::string const & value ) const {
//	std::cout << "create int16(" << value << ")" << std::endl;
	return (new Int16_t(this, value));
}

IOperand const *	Calculator::createInt32( std::string const & value ) const {
//	std::cout << "create int32(" << value << ")" << std::endl;
	return (new Int32_t(this, value));
}

IOperand const *	Calculator::createFloat( std::string const & value ) const {
//	std::cout << "create float(" << value << ")" << std::endl;
	return (new Float_t(this, value));
}

IOperand const *	Calculator::createDouble( std::string const & value ) const {
//	std::cout << "create double(" << value << ")" << std::endl;
	return (new Double_t(this, value));
}

/*
**  EXCEPTION
*/

Calculator::SyntaxError::SyntaxError( std::vector<std::string> v_error ) : std::exception(), error(v_error) {}
Calculator::SyntaxError::SyntaxError( SyntaxError const & src ) : std::exception(src) { *this = src; return; }
Calculator::SyntaxError::~SyntaxError( void ) throw() { return; }
Calculator::SyntaxError & Calculator::SyntaxError::operator=( SyntaxError const & rhs ) { (void) rhs; return *this; }
const char* Calculator::SyntaxError::what() const throw() {
	std::string*		str = new std::string("");
	str->append("Syntax error.\n");
	for (std::vector<std::string>::const_iterator it = this->error.begin() ; it != this->error.end(); ++it)
		str->append(*it);
	return (str->c_str());
}

/*
**  Parse Member
*/

void				Calculator::prompted( void ) {
	std::string		line;

	while ( std::getline(std::cin, line) ) {
		if (line.compare(";;") == 0)
			break;
		if (line.size() != 0)
			this->_script->push_back(line);
	}
	if (this->_script->size() == 0) {
		throw Calculator::NoInstruction();
		throw Calculator::NoInstruction();
	}
	//try {
		this->checkSyntax();
	//} catch ( Calculator::SyntaxError & e ) {
	//	std::cerr << "Error : " << e.what();
	//}
	return;
}

void				Calculator::scripted( char* file ) {
	std::ifstream	rFile(file);
	std::string		line;

	if (rFile.is_open()) {
		while ( std::getline(rFile, line) ) {
			if (line.size() != 0)
				this->_script->push_back(line);
		}
		if (this->_script->size() == 0)
			throw Calculator::NoInstruction();
		rFile.close();
		//try {
			this->checkSyntax();
		//} catch ( Calculator::SyntaxError & e ) {
		//	std::cerr << "Error : " << e.what();
		//}
	} else {
		throw Calculator::OpenError();
	}
	return;
}

/*
**  SYNTAX CHECK
*/

void			Calculator::checkSyntax()
{
	std::vector<std::string>::iterator	begin	= this->_script->begin();
	std::vector<std::string>::iterator	end		= this->_script->end();
	bool								error	= false;
	for(; begin != end; ++begin)
	{
		this->_count_line++;
		if (this->testCmd(*begin) == -1)
			error = true;
	}
	if (error)
		throw Calculator::SyntaxError(*this->_error);
}

int				Calculator::testCmd(std::string line)
{
	std::stringstream ss;
	int	ret;

	if (this->verifComment(line))
		return (0);
	if (this->verifEmpty(line))
		return (0);
	ret = this->verifAssertAndPush(line);
	if (ret == 0)
		ret = this->verifOtherCmd(line);
	if (ret == 0)
	{
		ss << "LINE " << this->_count_line << ": Command not found." << std::endl;
		this->_error->push_back(ss.str());
		return (-1);
	}
	if (ret == -1)
		return (-1);
	return (1);
}

int				Calculator::verifComment(std::string line)
{
	std::regex	e("^[\\s]*;.*$");
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (1);
	return (0);
}

int				Calculator::verifEmpty(std::string line)
{
	std::regex	e("^[\\s]*$");
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (1);
	return (0);
}

int				Calculator::verifAssertAndPush(std::string line)
{
	std::regex	e("^[\\s]*(push|assert)\\b.*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (this->verifAssertAndPushType(line));
	return (0);
}

int				Calculator::verifAssertAndPushType(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(?:push|assert)[\\s]+(int(?:8|16|32)|float|double)\\b.*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
	{
		std::string type = m[1].str();
		std::transform(type.begin(), type.end(), type.begin(), ::tolower);

		if (type == "int8" || type == "int16" || type == "int32")
			return (this->verifAssertAndPushIntValue(line));
		if (type == "float" || type == "double")
			return (this->verifAssertAndPushFloatValue(line));
	}
	ss << "LINE " << Calculator::_count_line << ": Type not valid." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

int				Calculator::verifAssertAndPushIntValue(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(push|assert)[\\s]+(int(?:8|16|32))[\\s]*\\([\\s]*([-]?[0-9]+)[\\s]*\\).*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (this->verifAssertAndPushIntExtraChar(line));
	ss << "LINE " << Calculator::_count_line << ": Value not valid." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

int				Calculator::verifAssertAndPushIntExtraChar(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(push|assert)[\\s]+(int(?:8|16|32))[\\s]*\\([\\s]*([-]?[0-9]+)[\\s]*\\)[\\s]*(?:;.*)*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (1);
	ss << "LINE " << Calculator::_count_line << ": Extra character(s) end of line." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

int				Calculator::verifAssertAndPushFloatValue(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(push|assert)[\\s]+(float|double)[\\s]*\\([\\s]*([-]?[0-9]+\\.[0-9]+)[\\s]*\\).*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (this->verifAssertAndPushFloatExtraChar(line));
	ss << "LINE " << Calculator::_count_line << ": Value not valid." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

int				Calculator::verifAssertAndPushFloatExtraChar(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(push|assert)[\\s]+(float|double)[\\s]*\\([\\s]*([-]?[0-9]+\\.[0-9]+)[\\s]*\\)[\\s]*(?:;.*)*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (1);
	ss << "LINE " << Calculator::_count_line << ": Extra character(s) end of line." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

int				Calculator::verifOtherCmd(std::string line)
{
	std::regex	e("^[\\s]*(pop|dump|add|sub|mul|div|mod|print|exit)\\b.*(?:;.*)*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (this->verifOtherCmdExtraChar(line));
	return (0);
}

int				Calculator::verifOtherCmdExtraChar(std::string line)
{
	std::stringstream ss;
	std::regex	e("^[\\s]*(pop|dump|add|sub|mul|div|mod|print|exit)[\\s]*(?:;.*)*$", std::regex_constants::icase);
	std::smatch	m;
	if ((std::regex_search (line,m,e)))
		return (1);
	ss << "LINE " << Calculator::_count_line << ": Extra character(s) end of line." << std::endl;
	this->_error->push_back(ss.str());
	return (-1);
}

/*
**	Execution Member
*/

void			Calculator::push( std::string type, std::string val )
{
	this->_stack->insert(this->_stack->begin(), this->createOperand( this->_type->at(type) , val));
	return;
}

void			Calculator::pop( void )
{
	if (this->_stack->size() == 0)
		throw Calculator::StackEmpty();
	this->_stack->erase(this->_stack->begin());
	return;
}

void			Calculator::dump( void )
{
	for (std::vector<IOperand const *>::const_iterator i = _stack->begin(); i != _stack->end(); ++i)
		std::cout << (*i)->toString() << std::endl;
	return;
}

void			Calculator::assert( std::string type, std::string val )
{
	IOperand const *	v1 = this->_stack->front();
	IOperand const *	cmp;
	cmp = this->createOperand( this->_type->at(type), val);
	if (v1->getType() == cmp->getType()
		&& v1->toString() == cmp->toString())
		return;
	throw AssertError();
}

void			Calculator::add( void )
{
	IOperand const * v1 = this->_stack->front();
	this->pop();

	IOperand const * v2 = this->_stack->front();
	this->pop();

	this->_stack->insert(this->_stack->begin(),*v2 + *v1);
	return;
}

void			Calculator::sub( void )
{
	IOperand const * v1 = this->_stack->front();
	this->pop();

	IOperand const * v2 = this->_stack->front();
	this->pop();

	this->_stack->insert(this->_stack->begin(),*v2 - *v1);
	return;
}

void			Calculator::mul( void )
{
	IOperand const * v1 = this->_stack->front();
	this->pop();

	IOperand const * v2 = this->_stack->front();
	this->pop();

	this->_stack->insert(this->_stack->begin(),*v2 * *v1);
	return;
}

void			Calculator::div( void )
{
	IOperand const * v1 = this->_stack->front();
	this->pop();

	IOperand const * v2 = this->_stack->front();
	this->pop();

	this->_stack->insert(this->_stack->begin(),*v2 / *v1);
	return;
}

void			Calculator::mod( void )
{
	IOperand const * v1 = this->_stack->front();
	this->pop();

	IOperand const * v2 = this->_stack->front();
	this->pop();

	this->_stack->insert(this->_stack->begin(),*v2 % *v1);
	return;
}

void			Calculator::print( void )
{
	IOperand const * v1 = this->_stack->front();
	Int8_t const * i = reinterpret_cast<Int8_t const *>(v1);
	if (v1->getType() != Int8 && i->getValue() > 0)
		throw Calculator::AssertError();
	std::cout << static_cast<char>(i->getValue()) << std::endl;
	return;
}

/*
**	Process stack
*/

void			Calculator::process()
{
	for (std::vector<std::string>::const_iterator i = _script->begin(); i != _script->end(); ++i) {
		std::string tmp = *i;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp == "exit")
		{
			return;
		}
		else if ( this->verifAssertAndPush(tmp) )
		{

			std::regex	e("^[\\s]*(push|assert)[\\s]+(int(?:8|16|32)|float|double)[\\s]*\\([\\s]*([-]?[0-9]+\\.*[0-9]+)[\\s]*\\)[\\s]*(?:;.*)*$");
			std::smatch	m;
			std::regex_search (tmp,m,e);
			MFPS pf = this->_eOpArg[m[1]];
			(this->*pf)(m[2], m[3]);
		}
		else if ( this->verifOtherCmd(tmp) )
		{
			MFPV pf = this->_eOp[tmp];
			(this->*pf)();
		}
	}
	throw NoExitError();
}



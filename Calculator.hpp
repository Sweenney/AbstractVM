/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 18:50:50 by tdemay            #+#    #+#             */
/*   Updated: 2015/06/08 13:11:20 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

# include <regex>
# include <fstream>
# include <stdexcept>
# include <vector>
# include <map>
# include <iterator>
# include <algorithm>
# include <string>
# include "IOperand.hpp"
# include "Int8_t.hpp"
# include "Int16_t.hpp"
# include "Int32_t.hpp"
# include "Float_t.hpp"
# include "Double_t.hpp"

class Calculator {

public:
	Calculator( void );
	~Calculator( void );

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	void		prompted( void );
	void		scripted( char* file );
	void		process( void );

	/*
	** EXECUTION METHODS
	*/

	void		push( std::string type, std::string val );
	void		pop( void );
	void		dump( void );
	void		assert( std::string type, std::string val );
	void		add( void );
	void		sub( void );
	void		mul( void );
	void		div( void );
	void		mod( void );
	void		print( void );
	void		exit( void );

	/*
	** EXCEPTIONS EXECUTION
	*/

	class	StackEmpty : public std::exception {
		public:
			StackEmpty( void ) : std::exception() {};
			StackEmpty( StackEmpty const & src ) : std::exception(src) { *this = src; return; };
			virtual ~StackEmpty( void ) throw() { return; };
			StackEmpty & operator=( StackEmpty const & rhs ) { (void) rhs; return *this; };
			virtual const char* what() const throw() { return ("Stack is empty."); };
	};

	class	AssertError : public std::exception {
		public:
			AssertError( void ) : std::exception() {};
			AssertError( AssertError const & src ) : std::exception(src) { *this = src; return; };
			virtual ~AssertError( void ) throw() { return; };
			AssertError & operator=( AssertError const & rhs ) { (void) rhs; return *this; };
			virtual const char* what() const throw() { return ("Assertion error."); };
	};

	class	NoExitError : public std::exception {
		public:
			NoExitError( void ) : std::exception() {};
			NoExitError( NoExitError const & src ) : std::exception(src) { *this = src; return; };
			virtual ~NoExitError( void ) throw() { return; };
			NoExitError & operator=( NoExitError const & rhs ) { (void) rhs; return *this; };
			virtual const char* what() const throw() { return ("No exit at end."); };
	};

	/*
	** SYNTAX
	*/

	void		checkSyntax( void );
	int			testCmd( std::string line );
	int			verifComment( std::string line );
	int			verifEmpty( std::string line );
	int			verifAssertAndPush( std::string line );
	int			verifAssertAndPushType( std::string line );
	int			verifAssertAndPushIntValue( std::string line );
	int			verifAssertAndPushIntExtraChar( std::string line );
	int			verifAssertAndPushFloatValue( std::string line );
	int			verifAssertAndPushFloatExtraChar( std::string line );
	int			verifOtherCmd( std::string line );
	int			verifOtherCmdExtraChar( std::string line );

	/*
	** EXCEPTIONS SYNTAX
	*/

	class	OpenError : public std::exception {
		public:
			OpenError( void ) : std::exception() {};
			OpenError( OpenError const & src ) : std::exception(src) { *this = src; return; };
			virtual ~OpenError( void ) throw() { return; };
			OpenError & operator=( OpenError const & rhs ) { (void) rhs; return *this; };
			virtual const char* what() const throw() { return ("Open file failed."); };
	};

	class	NoInstruction : public std::exception {
		public:
			NoInstruction( void ) : std::exception() {};
			NoInstruction( NoInstruction const & src ) : std::exception(src) { *this = src; return; };
			virtual ~NoInstruction( void ) throw() { return; };
			NoInstruction & operator=( NoInstruction const & rhs ) { (void) rhs; return *this; };
			virtual const char* what() const throw() { return ("No instruction found."); };
	};

	class	SyntaxError : public std::exception {
		public:
			SyntaxError( std::vector<std::string> v_error );
			SyntaxError( SyntaxError const & src );
			virtual ~SyntaxError( void ) throw();
			SyntaxError & operator=( SyntaxError const & rhs );
			virtual const char* what() const throw();
		private:
			std::vector<std::string>	error;
	};

private:
	typedef IOperand const *	(Calculator::*MFP)(std::string const &) const;
	typedef void				(Calculator::*MFPS)(std::string, std::string);
	typedef void				(Calculator::*MFPV)(void);
	MFP										_eCreate[5];
	std::map<std::string, MFPS>				_eOpArg;
	std::map<std::string, MFPV>				_eOp;
	std::map<std::string, eOperandType>*	_type;
	std::vector<std::string>*				_script;
	std::vector<IOperand const*>*			_stack;
	std::vector<std::string>*				_error;
	int										_count_line;

	IOperand const *			createInt8( std::string const & value ) const;
	IOperand const *			createInt16( std::string const & value ) const;
	IOperand const *			createInt32( std::string const & value ) const;
	IOperand const *			createFloat( std::string const & value ) const;
	IOperand const *			createDouble( std::string const & value ) const;

	Calculator( Calculator const & src );
	Calculator&	operator=( Calculator const & src );
};

#else

class Calculator;

#endif /* CALCULATOR_HPP */

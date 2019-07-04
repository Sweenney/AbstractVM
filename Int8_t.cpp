/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8_t.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 17:37:19 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:25:59 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Int8_t.hpp"

Int8_t::Int8_t( Calculator const * c, std::string const & value ) {
	this->_value = std::stoi(value);
	this->_precision = 0;
	this->_calc = c;
	return;
}

Int8_t::~Int8_t( void ) {
	return;
}

Int8_t&				Int8_t::operator=( Int8_t const & src ) {
	if ( this != &src ) {
		this->_value = src.getValue();
		this->_precision = src.getPrecision();
	}
	return *this;
}

int						Int8_t::getPrecision( void ) const {
	return this->_precision;
}

eOperandType			Int8_t::getType( void ) const {
	return Int8;
}

int8_t					Int8_t::getValue( void ) const {
	return this->_value;
}

IOperand const *		Int8_t::operator+( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value + t));
	return ret;
}

IOperand const *		Int8_t::operator-( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value - t));
	return ret;
}

IOperand const *		Int8_t::operator*( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value * t));
	return ret;
}

IOperand const *		Int8_t::operator/( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value / t));
	return ret;
}

IOperand const *		Int8_t::operator%( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(fmod(this->_value, t)));
	return ret;
}

std::string const &		Int8_t::toString( void ) const {
	std::stringstream	ss;
	ss.precision(this->_precision);
	ss << (int)this->_value;
	std::string *ret = new std::string(ss.str().data());
	return *ret;
}


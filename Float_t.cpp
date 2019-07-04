/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float_t.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 17:37:19 by tdemay            #+#    #+#             */
/*   Updated: 2015/06/08 13:05:32 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Float_t.hpp"

Float_t::Float_t( Calculator const * c, std::string const & value ) {
	this->_value = std::stof(value);
	this->_precision = value.substr(value.find(".")).length() + 1;
	this->_calc = c;
	return;
}

Float_t::~Float_t( void ) {
	return;
}

Float_t&				Float_t::operator=( Float_t const & src ) {
	if ( this != &src ) {
		this->_value = src.getValue();
		this->_precision = src.getPrecision();
	}
	return *this;
}

int						Float_t::getPrecision( void ) const {
	return this->_precision;
}

eOperandType			Float_t::getType( void ) const {
	return Float;
}

float					Float_t::getValue( void ) const {
	return this->_value;
}

IOperand const *		Float_t::operator+( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value + t));
	return ret;
}

IOperand const *		Float_t::operator-( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value - t));
	return ret;
}

IOperand const *		Float_t::operator*( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value * t));
	return ret;
}

IOperand const *		Float_t::operator/( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value / t));
	return ret;
}

IOperand const *		Float_t::operator%( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(fmod(this->_value, t)));
	return ret;
}


std::string const &		Float_t::toString( void ) const {
	std::stringstream	ss;
	ss.precision(this->_precision);
	ss << this->_value;
	std::string *ret = new std::string(ss.str().data());
	return *ret;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Double_t.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 17:37:19 by tdemay            #+#    #+#             */
/*   Updated: 2015/06/08 13:09:36 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Double_t.hpp"

Double_t::Double_t( Calculator const * c, std::string const & value ) {
	this->_value = std::stod(value);
	this->_precision = value.substr(value.find(".")).length() + 1;
	this->_calc = c;
	return;
}

Double_t::~Double_t( void ) {
	return;
}

Double_t&				Double_t::operator=( Double_t const & src ) {
	if ( this != &src ) {
		this->_value = src.getValue();
		this->_precision = src.getPrecision();
	}
	return *this;
}

int						Double_t::getPrecision( void ) const {
	return this->_precision;
}

eOperandType			Double_t::getType( void ) const {
	return Double;
}

double					Double_t::getValue( void ) const {
	return this->_value;
}

IOperand const *		Double_t::operator+( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value + t));
	return ret;
}

IOperand const *		Double_t::operator-( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value - t));
	return ret;
}

IOperand const *		Double_t::operator*( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value * t));
	return ret;
}

IOperand const *		Double_t::operator/( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(this->_value / t));
	return ret;
}

IOperand const *		Double_t::operator%( IOperand const & rhs ) const {
	eOperandType	type = (rhs.getType() > Int8) ? rhs.getType() : Int8;
	IOperand const *		ret = NULL;
	double  t = std::atof(rhs.toString().data());
	ret = this->_calc->createOperand(type, std::to_string(fmod(this->_value, t)));
	return ret;
}

std::string const &		Double_t::toString( void ) const {
	std::stringstream	ss;
	ss.precision(this->_precision);
	ss << this->_value;
	std::string *ret = new std::string(ss.str().data());
	return *ret;
}


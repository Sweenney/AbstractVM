/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:28:25 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:01:09 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <iostream>
# include <sstream>
# include <cstdlib>
# include <cmath>

enum eOperandType {
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand {

public:
	virtual int getPrecision( void ) const = 0;									// Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0;								// Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0;		// Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0;		// Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0;		// Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0;		// Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0;		// Modulo
	virtual std::string const & toString( void ) const = 0;						// String representation of the instance
	virtual ~IOperand( void ) {}

};

#else

class IOperand;

#endif /* IOPERAND_HPP */

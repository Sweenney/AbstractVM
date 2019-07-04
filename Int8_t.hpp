/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8_t.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 16:17:16 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:25:49 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT8_T_HPP
# define INT8_T_HPP

# include "IOperand.hpp"
# include "Calculator.hpp"

class Int8_t : public IOperand {

public:
	Int8_t( Calculator const * c, std::string const & value );
	virtual							~Int8_t( void );

	Int8_t&							operator=( Int8_t const & src );

	/* IOperation Implementation */
	virtual int						getPrecision( void ) const;					// Precision of the type of the instance
	virtual eOperandType			getType( void ) const;						// Type of the instance
	virtual IOperand const *		operator+( IOperand const & rhs ) const;	// Sum
	virtual IOperand const *		operator-( IOperand const & rhs ) const;	// Difference
	virtual IOperand const *		operator*( IOperand const & rhs ) const;	// Product
	virtual IOperand const *		operator/( IOperand const & rhs ) const;	// Quotient
	virtual IOperand const *		operator%( IOperand const & rhs ) const;	// Modulo
	virtual std::string const &		toString( void ) const;

	/* Getter */
	int8_t							getValue( void ) const;

private:
	mutable int8_t		_value;
	int					_precision;
	Calculator const *	_calc;

	Int8_t( void );
	Int8_t( Int8_t const & src );

};

#else

class Int8_t;

#endif /* INT8_T_HPP */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int16_t.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 16:18:21 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:25:26 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT16_T_HPP
# define INT16_T_HPP

# include "IOperand.hpp"
# include "Calculator.hpp"

class Int16_t : public IOperand {

public:
	Int16_t( Calculator const * c, std::string const & value );
	virtual							~Int16_t( void );

	Int16_t&						operator=( Int16_t const & src );

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
	int16_t							getValue( void ) const;

private:
	mutable int16_t		_value;
	int					_precision;
	Calculator const *	_calc;

	Int16_t( void );
	Int16_t( Int16_t const & src );

};

#else

class Int16_t;

#endif /* INT16_T_HPP */

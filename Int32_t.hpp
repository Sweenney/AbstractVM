/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int32_t.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 16:19:12 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:25:04 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT32_T_HPP
# define INT32_T_HPP

# include "IOperand.hpp"
# include "Calculator.hpp"

class Int32_t : public IOperand {

public:
	Int32_t( Calculator const * c, std::string const & value );
	virtual							~Int32_t( void );

	Int32_t&						operator=( Int32_t const & src );

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
	int32_t							getValue( void ) const;

private:
	mutable int32_t		_value;
	int					_precision;
	Calculator const *	_calc;

	Int32_t( void );
	Int32_t( Int32_t const & src );

};

#else

class Int32_t;

#endif /* INT32_T_HPP */

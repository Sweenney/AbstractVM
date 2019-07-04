/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float_t.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 16:19:57 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:24:35 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_HPP
# define FLOAT_HPP

# include "IOperand.hpp"
# include "Calculator.hpp"

class Float_t : public IOperand {

public:
	Float_t( Calculator const * c, std::string const & value );
	virtual							~Float_t( void );

	Float_t&						operator=( Float_t const & src );

	/* IOperation Implementation */
	virtual int						getPrecision( void ) const;										// Precision of the type of the instance
	virtual eOperandType			getType( void ) const;									// Type of the instance
	virtual IOperand const *		operator+( IOperand const & rhs ) const;			// Sum
	virtual IOperand const *		operator-( IOperand const & rhs ) const;			// Difference
	virtual IOperand const *		operator*( IOperand const & rhs ) const;			// Product
	virtual IOperand const *		operator/( IOperand const & rhs ) const;			// Quotient
	virtual IOperand const *		operator%( IOperand const & rhs ) const;			// Modulo
	virtual std::string const &		toString( void ) const;

	/* Getter */
	float							getValue( void ) const;

private:
	mutable float		_value;
	int					_precision;
	Calculator const *	_calc;

	Float_t( void );
	Float_t( Float_t const & src );

};

#else

class Float_t;

#endif /* FLOAT_HPP */

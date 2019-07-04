/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Double_t.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 16:20:32 by tdemay            #+#    #+#             */
/*   Updated: 2015/02/06 17:24:53 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_HPP
# define DOUBLE_HPP

# include "IOperand.hpp"
# include "Calculator.hpp"

class Double_t : public IOperand {

public:
	Double_t( Calculator const * c, std::string const & value );
	virtual							~Double_t( void );

	Double_t&						operator=( Double_t const & src );

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
	double							getValue( void ) const;

private:
	mutable double		_value;
	int					_precision;
	Calculator const *	_calc;

	Double_t( void );
	Double_t( Double_t const & src );

};

#else

class Double_t;

#endif /* DOUBLE_HPP */

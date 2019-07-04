/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 16:11:21 by tdemay            #+#    #+#             */
/*   Updated: 2015/06/08 14:35:28 by tdemay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include "Calculator.hpp"

/*
int		main( void ) {
	Calculator	c;
	IOperand const *	res = NULL;
	IOperand const *	lhs = c.createOperand( Int8, "6.1234");
	IOperand const *	rhs = c.createOperand( Double, "6.1234567");
	IOperand const *	grhs = c.createOperand( Double, "6.1234567");
	std::cout << lhs->toString() << " + " << rhs->toString();
	res = *lhs + *rhs;
	std::cout << " = " << res->toString() << " + " << grhs->toString() << std::endl;
	res = *res + *grhs;
	std::cout << " = " << res->toString() << std::endl;
	return (0);
}
*/

void	usage( char *exec ) {
	std::cout << "usage: " << exec;
	// usage for this executable
	std::cout << " [file]" << std::endl;
	std::cout << "\t- Without options exectutable read on stdin" << std::endl;
	std::cout << "\t- With option file executable read in file" << std::endl;
	return;
}

int		main( int ac, char ** av ) {
	Calculator	c;

	if ( ac == 1 )
		try {
			c.prompted();
			std::cout << "exec" << std::endl;
			c.process();
		} catch ( std::exception & e) {
			std::cerr << "Error: " << e.what();
		}
	else if ( ac == 2 )
		try {
			c.scripted(av[1]);
			std::cout << "exec" << std::endl;
			c.process();
		} catch ( std::exception & e) {
			std::cerr << "Error: " << e.what();
		}
	else
		usage( av[0] );
	return (0);
}

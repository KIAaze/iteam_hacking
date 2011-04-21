#ifndef _GP_EXCEPTION_H_
#define _GP_EXCEPTION_H_

#include <string>
#include <exception>
#include <iostream>

/*! \namespace gp
    \brief The namespace used for gamepower.
*/
namespace gp {

/**
 * The GPException is the base class for every exception within the GP
 * framework. It extends the std::exception class (as recommended by various
 * sites and people from IRC on ##c++ on Freenode).
 *
 * Feel free to extend this class within the GP framework to make custom
 * exceptions.
 *
 * TODO: make use of char* to adhere to the standard of std::exception (IRC logs)
 *
 * @author krpors
 */
class GPException : public std::exception {
private:

    /// The description of the GPException.
    std::string m_what;

    /// Detail of the exception.
    std::string m_detail;

    /// Used to concatenate what and detail.
    std::string m_concat;

public:
    /**
     * Creates the GPException provided with a descriptive string.
     *
     * @param description The string used to describe what the exception
     *   actually is.
     * @param detail A detail message. Default is "" (an empty string).
     */
    explicit GPException(std::string description, std::string detail = "");

    /**
     * Destructor of the GPException.
     */
    virtual ~GPException() throw();

    /**
     * Gets the (optional) extra detail of the exception. For instance, if
     * SDL generates an error, this error could be returned by this method.
     *
     * @return The detail message, optional.
     */
    const std::string getDetail() const throw();

    /**
     * Gets the description of the GPException. It's an overridden function
     * from the std::exception class.
     *
     * @return The description of the exception.
     */
    const char* what() const throw();
};

}

#endif

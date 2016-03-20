#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include "xml.h"

using namespace xercesc;

bool ParseXML( const std::string& filename, std::vector<Task>& tasks )
{
    bool result = false;

    try
    {
        XMLPlatformUtils::Initialize();

        XercesDOMParser* parser = new XercesDOMParser();
        if( parser )
        {
            parser->setValidationScheme( XercesDOMParser::Val_Always );

            ErrorHandler* errorHandler = ( ErrorHandler* ) new HandlerBase();
            if( errorHandler )
            {
                parser->setErrorHandler( errorHandler );

                parser->parse( filename.c_str() );

                result = true;

                delete errorHandler;
            }

            delete parser;
        }
    }
    catch( const XMLException& exception )
    {
    }

    XMLPlatformUtils::Terminate();

    return result;
}


#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOM.hpp>

#include "xml.h"

using namespace xercesc;

static bool ParseNode( DOMNode* node, std::vector<Task>& tasks )
{
    bool result = false;
    DOMNamedNodeMap* attributeMap = NULL;
    DOMNode* typeNode = NULL;
    std::string nodeName( XMLString::transcode( node->getNodeName() ) );
    std::string typeNodeName;
    std::string typeStr;

    if( "task" == nodeName )
    {
        attributeMap = node->getAttributes();
        if( attributeMap )
        {
            typeNode = attributeMap->item( 0 );
            if( typeNode )
            {
                typeNodeName = std::string( XMLString::transcode( typeNode->getNodeName() ) );
                if( "type" == typeNodeName )
                {
                    typeStr = std::string( XMLString::transcode( typeNode->getNodeValue() ) );

                    if( "host_set_current_directory" == typeStr )
                    {
                        result = true;
                    }
                    else if( "host_run_program" == typeStr )
                    {
                        result = true;
                    }
                    else if( "vm_revert" == typeStr )
                    {
                        result = true;
                    }
                    else if( "vm_file_copy" == typeStr )
                    {
                        result = true;
                    }
                    else if( "vm_run_program" == typeStr )
                    {
                        result = true;
                    }
                    else
                    {
                        std::cout << "Unsupported task type." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid type attribute." << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to get type attribute." << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get task node attributes." << std::endl;
        }
    }
    else if( "#text" == nodeName )
    {
        // Empty text node, skip it.
        result = true;
    }
    else
    {
        std::cout << "Invalid task node name: " << nodeName << std::endl;
    }

    return result;
}

bool ParseXML( const std::string& filename, std::vector<Task>& tasks )
{
    bool result = false;
    XercesDOMParser* parser = NULL;
    ErrorHandler* errorHandler = NULL;
    DOMDocument* document = NULL;
    DOMElement* rootElement = NULL;
    DOMNodeIterator* documentIterator = NULL;
    DOMNode* rootNode = NULL;
    DOMNodeList* taskNodes = NULL;
    DOMNode* currentNode = NULL;
    std::string nodeName;

    try
    {
        XMLPlatformUtils::Initialize();

        parser = new XercesDOMParser();
        if( parser )
        {
            parser->setValidationScheme( XercesDOMParser::Val_Always );

            errorHandler = ( ErrorHandler* ) new HandlerBase();
            if( errorHandler )
            {
                parser->setErrorHandler( errorHandler );

                parser->parse( filename.c_str() );

                document = parser->getDocument();
                if( document )
                {
                    rootElement = document->getDocumentElement();
                    if( rootElement )
                    {
                        documentIterator = document->createNodeIterator( rootElement,
                                                                         DOMNodeFilter::SHOW_ELEMENT,
                                                                         NULL,
                                                                         true );
                        if( documentIterator )
                        {
                            rootNode = documentIterator->nextNode();
                            if( rootNode )
                            {
                                nodeName = std::string( XMLString::transcode( rootNode->getNodeName() ) );
                                if( "turnaround" == nodeName )
                                {
                                    taskNodes = rootNode->getChildNodes();
                                    if( taskNodes )
                                    {
                                        result = true;

                                        for( int i = 0; i < taskNodes->getLength() && result; i++ )
                                        {
                                            currentNode = taskNodes->item( i );
                                            if( currentNode )
                                            {
                                                result = ParseNode( currentNode, tasks );
                                            }
                                            else
                                            {
                                                result = false;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "Failed to create task iterator." << std::endl;
                                    }
                                }
                                else
                                {
                                    std::cout << "Invalid root node name." << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "Failed to get root node." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to create iterator." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Failed to get root element." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Failed to get document." << std::endl;
                }

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


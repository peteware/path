/**
 * @file main.cpp search/main.cpp
 * @defgroup SearchTest Test applicaiton that searches for files
 */
#include <path/Node.h>
#include <path/NodeIter.h>
#include <path/Canonical.h>
#include <path/PathException.h>
#include <path/FileStream.h>
#include <path/SysCalls.h>

#include <getopt.h>
#include <iostream>

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

void count(std::ostream &out, path::Node &node);
/**
 * Test applicaton that uses the Path library to search
 * for files
 *
 */
int main(int argc, char **argv)
{
	int		ch;		// Input option
	size_t	size = 0;	// Size of the file to search for
	char *	name;	// Name of the file to search
    bool    countLines = false;  // Should lines be counted?
	/* options descriptor */
	static struct option longopts[] = {
		{ "size",		required_argument,      NULL,           's' },
		{ "name",   	required_argument,      NULL,           'n' },
		{ "line",   	no_argument,            NULL,           'l' },
        { NULL,         0,                      NULL,           0 }
	};

	while ((ch = getopt_long(argc, argv, "ls:n:", longopts, NULL)) != -1)
	{
		switch (ch)
		{
		case 's':
			size = atoi(optarg);
			break;
		case 'n':
			name = optarg;
			break;
        case 'l':
            countLines = true;
            break;
		default:
			exit(1);
			break;
		}
	}
	const path::PathRules *rules = path::System.rules();
	for (int i = optind; i < argc; ++i)
	{
        try
        {
            path::Node	node (path::Path(rules->canonical(argv[i])));
            std::cout << "start " << node.path() << std::endl;
            for (path::Node::iterator iter = node.begin().setRecursive(); iter != node.end(); ++iter)
            {
                if (size > static_cast<size_t>(0) && iter->size() < size)
                    continue;
                if (countLines)
                    count(std::cout, *iter);
                else 
                {
                    std::cout << iter->path();
                    if (iter->isDir())
                        std::cout << '/';
                    std::cout << std::endl;
                }
            }
        }
        catch (path::PathException ex)
        {
			std::cerr << ex.what() << std::endl;
        }
	}
	
}

/**
 * Print the filename and number of lines for a Node
 * 
 * @param out The output stream, usualy std::cout, to print to
 * @param node the Node to count the number of lines
 */
void count(std::ostream &out, path::Node &node)
{
    path::FileStream    str (node, std::ios_base::binary);
    char    ch;
    int     count = 0;

    while (str) {
        str >> ch;
        if (ch == '\n' || ch == '\r')
            ++count;
    }
    out << str.path() << ':' << count << std::endl;
}

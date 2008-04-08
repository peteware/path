#include <path/Node.h>
#include <path/NodeIter.h>
#include <path/Canonical.h>
#include <path/PathException.h>

#include <getopt.h>
#include <iostream>

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

int main(int argc, char **argv)
{
	int		ch;		// Input option
	size_t	size;	// Size of the file to search for
	char *	name;	// Name of the file to search
	/* options descriptor */
	static struct option longopts[] = {
		{ "size",		required_argument,      NULL,           's' },
		{ "name",   	required_argument,      NULL,           'n' },
		{ NULL,         0,                      NULL,           0 }
	};

	while ((ch = getopt_long(argc, argv, "s:n:", longopts, NULL)) != -1)
	{
		switch (ch)
		{
		case 's':
			size = atoi(optarg);
			break;
		case 'n':
			name = optarg;
			break;
		default:
			exit(1);
			break;
		}
	}
	
	for (int i = optind; i < argc; ++i)
	{
        try
        {
            Node	node (Path(UnixPath(argv[i])));
            std::cout << node.path() << std::endl;
            for (Node::iterator iter = node.begin(); iter != node.end(); ++iter)
            {
                if (size > 0 && iter->size() < size)
                    continue;
                std::cout << iter->path();
                if (iter->isDir())
                    std::cout << '/';
                std::cout << std::endl;
            }
        }
        catch (PathException ex)
        {
			std::cerr << ex.what() << std::endl;
        }
	}
	
}

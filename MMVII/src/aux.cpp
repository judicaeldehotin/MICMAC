void  ShowArgs(int argc, char ** argv)
{
    for (int aK=0 ; aK<argc ; aK++)
        std::cout  << "Arg[" << aK << "]=" << argv[aK] << "\n";
}

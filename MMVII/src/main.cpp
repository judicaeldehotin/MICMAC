#include "../include/MMVII_all.h"

using namespace std;
namespace MMVII {
static int SaveArgC;
static char ** SaveArgV;
  const std::string DirBin2007=MMVII_INSTALL_PATH;
void ShowArgsMain()
{
   std::cout << "========= ARGS OF COMMAND ==========\n";
   for (int aK=0 ; aK<SaveArgC ; aK++)
       std::cout << SaveArgV[aK] << " ";
   std::cout << "\n";
}
};

using namespace MMVII;



int main(int argc, char ** argv)
{
{
   StdOut() << "GGGGHHH " << __LINE__ << " at " << __FILE__ << "\n";
   return EXIT_SUCCESS;
}
   SaveArgC = argc;
   SaveArgV = argv;

   setlocale(LC_ALL, "C");
   //std::setlocale(LC_ALL, "C");
   // std::setlocale(LC_ALL, "en_US.UTF-8");

   // Debug, print command
   if (0)
   {
       StdOut() << "==========COMM=====   \n";
       for (int aK=0 ; aK<argc ; aK++)
       {
            if (aK) StdOut() << " ";
            StdOut() << argv[aK];
       }
       StdOut() << "\n";
   }

   if (argc>1)
   {
      std::string aNameCom = argv[1];

      // Recherche la specif correspondant au nom de commande
      cSpecMMVII_Appli*  aSpec = cSpecMMVII_Appli::SpecOfName(aNameCom,true);

      // Execute si match
      if (aSpec)
      {
         std::vector<std::string> aVArgs;
         for (int aK=0 ; aK<argc; aK++)
             aVArgs.push_back(argv[aK]);
         return aSpec->AllocExecuteDestruct(aVArgs);
      }
   }

   // Affiche toutes les commandes
   for (const auto & aSpec : cSpecMMVII_Appli::VecAll())
   {
       StdOut()  << aSpec->Name() << " => " << aSpec->Comment() << "\n";
   }
StdOut() << "GGGG " << __LINE__ << " at " << __FILE__ << "\n";
   return EXIT_SUCCESS;
}




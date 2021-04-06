#include "article.h"

Article::Article()
{
    month = rand() % 11 + 1;
    day = rand() % 27 + 1;
}

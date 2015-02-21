x <- 0

f <- function() 
{ 
	x <- 1 
}

g <- function() 
{
	if (x == 0) { print("Thanks R") }
}

f()
g()

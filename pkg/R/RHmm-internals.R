########## RHmm-Internals
setStorageMode <- function(object) UseMethod("setStorageMode")

setStorageMode.paramHMM <- function(object)
{   x <- object
    storage.mode(x$nStates) <- "integer"
    storage.mode(x$dimObs) <- "integer"
    storage.mode(x$nMixt) <- "integer"
    storage.mode(x$nLevels) <- "integer"
    storage.mode(x) <- "list"
    class(x) <- "paramHMM"
    return(x)
}

setStorageMode.paramAlgoBW <- function(object)
{   x <- object
    storage.mode(x$iter) <- "integer"
    storage.mode(x$verbose) <- "integer"
    storage.mode(x$nInit) <- "integer"
    storage.mode(x$nIterInit) <- "integer"
    if (!is.null(x$initPoint))
       x$initPoint <- setStorageMode(x$initPoint)
    storage.mode(x) <- "list"
    class(x) <- "paramAlgoBW"
    return(x)
}    

setStorageMode.HMMClass <- function(object)
{   x <- object
    storage.mode(x$initProb) <- "double"
    storage.mode(x$transMat) <- "double"
    x$distribution <- setStorageMode(object$distribution)
    class(x$distribution) <- class(object$distribution)
    storage.mode(x) <- "list"
    class(x) <- "HMMClass"
    return(x)
}

setStorageMode.distributionClass <- function(object)
{   x<-NextMethod("setStorageMode", object)
    storage.mode(x$nStates) <- "integer"
    return(x)
}

setStorageMode.univariateNormalClass <- function(object)
{   x <- object
    storage.mode(x$dimObs) <- "integer"
    storage.mode(x$mean) <- "double"
    storage.mode(x$var) <- "double"
    storage.mode(x) <- "list"
    class(x) <- c("distributionClass", "univariateNormalClass")
    return(x)
}

setStorageMode.multivariateNormalClass <- function(object)
{   x <- object
    storage.mode(x$dimObs) <- "integer"
    storage.mode(x$mean) <- "list"
    storage.mode(x$cov) <- "list"
    storage.mode(x) <- "list"
    class(x) <- c("distributionClass", "multivariateNormalClass")
    return(x)
}

setStorageMode.mixtureUnivariateNormalClass <- function(object)
{   x <- object
    storage.mode(x$dimObs) <- "integer"
    storage.mode(x$nMixt) <- "integer"
    storage.mode(x$mean) <- "list"
    storage.mode(x$var) <- "list"
    storage.mode(x$proportion) <- "list"
    storage.mode(x) <- "list"
    return(x)        
}

setStorageMode.mixtureMultivariateNormalClass <- function(object)
{   x <- object
    storage.mode(x$dimObs) <- "integer"
    storage.mode(x$nMixt) <- "integer"
    storage.mode(x$mean) <- "list"
    storage.mode(x$cov) <- "list"
    storage.mode(x$proportion) <- "list"
    storage.mode(x) <- "list"
    return(x)        
}

setStorageMode.discreteClass <- function(object)
{  x <- object
   storage.mode(x$nLevels) <- "integer"
   storage.mode(x) <- "list"
   return(x)        
}    

make_labels <- function(factorlist,labels)
{   l <- length(factorlist)
    Aux <- as.vector(factorlist[[1]])
    Res <- list(1)
    for (i in 2:l)
    {   x <- as.vector(factorlist[[i]])
        Aux <- c(Aux, x)
        Res <- c(Res, list(1))
    }
    
    Aux <- factor(Aux)
    nLevels <- length(labels)
    for (i in 1:l)
        Res[[i]] <- factor(factorlist[[i]], levels=labels)
    
    return(list(labels = labels, nLevels=nLevels, obs=Res))
}

transf_integer<-function(uneObs, label, nLevels)
{
    return(sum((1:nLevels)*(uneObs == label)))
}

TransformeListe <- function(paramHMM, obs)
{
    if (paramHMM$dis=='DISCRETE')
    {   if (is.list(obs))
        {   Y <- obs[[1]]
            for (i in 2:length(obs))
                Y <- c(Y, obs[[i]])
        }
        else
            Y <- obs
        proba <- rep(list(1), paramHMM$nStates)
        labels <- levels(factor(Y))
        nLevels <- length(levels(factor(Y)))
        for (j in 1:paramHMM$nStates)
            proba[[j]] <- rep(1,nLevels)/as.double(nLevels)            
        distribution<-distributionSet(dis="DISCRETE", proba, labels)
        return(TransformeList(distribution, obs))
    }
    else 
    {    if (is.list(obs))
         {   return(list(Zt=obs, nLevels=0, labels=NULL))
         }
         else
         {  return(list(Zt=list(obs), nLevels=0, labels=NULL))
         }
    }
}
        
TransformeList <- function(distribution, obs)
{   dis = distribution$dis
    nLevels <- 0
    labels <- NULL 
    if (is.list(obs))
    {   if (dis == "DISCRETE")
        {   labels <- labels(distribution$proba[[1]])
            nLevels <- distribution$nLevels
            Aux <- make_labels(obs,labels)
            nLevels <- Aux$nLevels
            Zt <- list(as.double(Aux$obs[[1]])-1)
            for (i in 2:length(obs))
                Zt <- c(Zt, list(as.double(Aux$obs[[i]])-1))
        }
        else
            Zt <- obs
    }
    else
    {   if (dis == "DISCRETE")
        {   labels <- labels(distribution$proba[[1]])
            nLevels <- distribution$nLevels
            nObs <- length(obs)
            if (! all(is.numeric(obs)))
            {   Aux <- rep(0, nObs)
                for (i in 1:nObs)
                    Aux[i] <- transf_integer(obs[i], labels, nLevels)
            }
            else
                Aux <- as.integer(obs) 
            Zt <- list(as.double(Aux)-1) 
        }
        else
            Zt <- list(obs)
    }
    return(list(Zt=Zt, nLevels = nLevels, labels = labels))
}


########## end of RHmm_internals

library(mongolite)
library(ggplot2)

setClass("mongostats", slots= list(url = "character"))

setGeneric(name="getMessages_perhour",
           def=function(obj)
           {
             standardGeneric("getMessages_perhour")
           }
)

setMethod("getMessages_perhour", "mongostats", 
          function(obj){
            connection = mongo("chats", url = obj@url)
            messages_per_hour <- connection$aggregate('[
                                                        {"$unwind" : "$messages"},
                                                        {"$project" : {"messages.content" : 1, 
                                                                        "time" : {"$dateToString": {"format": "%H",
                                                                        "date" : "$messages.receptionDate"}}}},
                                                        {"$group" : {"_id" : "$time", "count" : {"$sum" : 1} }}
                                                       ]', options = '{"allowDiskUse" : true}')
            names(messages_per_hour) <- c("time", "count")
            connection$disconnect()
            return(messages_per_hour)                                      
          })

setGeneric(name="showUsers",
           def=function(obj)
           {
             standardGeneric("showUsers")
           }
)

setMethod("showUsers", "mongostats", 
          function(obj){
            connection = mongo("users", url = obj@url)
            users <- connection$aggregate('[
                                            {"$project" : {"password" : 0}} 
                                           ]', options = '{"allowDiskUse" : true}')
            connection$disconnect()
            return(users)                                      
          })

setGeneric(name="showChatByUser",
           def=function(obj)
           {
             standardGeneric("showChatByUser")
           }
)

setMethod("showChatByUser", "mongostats",
          function(obj){
            connection = mongo("chats", url = obj@url)
            cat("\nPut user id: ")
            id <-readLines(n=1)
            query <- paste('[{"$match" : {"partecipants": "', id,'"}},
                             {"$unwind": "$messages"},
                             {"$match": {"messages.sender_id": "', id, '"}},
                             {"$project": { "_id": 1, "name" : 1, "isgroup" : 1, "messages.sender_id": 1}},
                             {"$group": {"_id": "$_id", "name" : { "$first": "$name" }, "isgroup" : { "$first": "$isgroup" }, "count": {"$sum":1}}}
                            ]', sep = "")
      

            chats <-connection$aggregate(query, options = '{"allowDiskUse" : true}')
            
          
            connection$disconnect()
            return(chats)
          })


setGeneric(name="getMessages_peruser",
           def=function(obj)
           {
             standardGeneric("getMessages_peruser")
           }
)

setMethod("getMessages_peruser", "mongostats",
          function(obj){
            connection = mongo("chats", url = obj@url)

            query <- '[{"$unwind": "$messages"},
                             {"$project": { "_id": 1, "messages.senderName": 1}},
                             {"$group": {"_id": "$messages.senderName", "count": {"$sum":1}}}
                            ]'
            
            messages <-connection$aggregate(query, options = '{"allowDiskUse" : true}')
            names(messages) <- c('user', 'count')
            
            connection$disconnect()
            return(messages)
          }
          )

setGeneric(name="showChats",
           def=function(obj)
           {
             standardGeneric("showChats")
           }
)

setMethod("showChats", "mongostats", 
          function(obj){
            connection = mongo("chats", url = obj@url)
            cat("\nPut user id: ")
            id <- readLines(n=1)
            query <- paste('[{"$match" : {"partecipants": "', id, '"}}]')
            print(query)
            chats <- connection$aggregate(query, options = '{"allowDiskUse" : true}')
            connection$disconnect()
            return(chats)                                      
          })


saveData <- function(d){
  cat("\nPut filename: ")
  filename <- readLines(n=1)
  filename <- trimws(filename)
  filename <- paste(filename, ".RData", sep="")
  save(d, file=filename)
  cat(paste("Object saved in ", filename))
}

loadData <- function(){
  cat("\nPut filename: ")
  filename <- readLines(n=1)
  filename <- trimws(filename)
  filename <- paste(filename, ".RData", sep="")
  loaded <- load(file=filename, globalenv())
  cat(paste("Loaded objects:", loaded, "\n"))
}

ms <- new("mongostats", url = "mongodb://5.79.72.99:27017/testdb")

repeat {
  cat("\n========== MENU ===========
     1. Show users
     2. Show chats by user
     3. Show messages per hour
     4. Show messages per user
     5. Save current data to file
     6. Load data from file
     7. Print current data
     Anything else to close me\n")
  cat("Make your choose: ")
  x <- readLines(n = 1)
  
  
  if(is.na(as.numeric(x))){
    break
  }
  
  x <- as.numeric(x)
  
  if (x == 1){
    d <- showUsers(ms)
    print(d)
    
    
  } else if( x == 2){
    
    d <-showChatByUser(ms)
    #d <- showChats(ms)
    print(d)
    
  } else if(x == 3){
    
    d <- getMessages_perhour(ms)
    plot <- ggplot(data = d, aes(time, count), environment = globalenv()) + geom_col()
    print(plot)
    
  } else if(x==4){
    d<-getMessages_peruser(ms)
    plot <- ggplot(data = d, aes(user, count), environment = globalenv()) + geom_col()
    print(plot)
    print(d)
  }else if( x == 5){
    saveData(d)
    
  } else if( x== 6){
    loadData()
  
  } else if( x== 7){
    print(d)
  } else {
    
    break;
  }
  
  
}

cat("See you to another time. Bye.\n")



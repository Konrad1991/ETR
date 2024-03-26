# from: https://stackoverflow.com/questions/6457290/how-to-check-the-amount-of-ram
available_memory <- function() {
  OS <- tolower(Sys.info()["sysname"])
  if(OS == "windows"){ 
    system_info <- system("systeminfo", intern = TRUE)
    value <- system_info[
      grep("Available Physical Memory", system_info)
    ]
    value <- gsub("Available Physical Memory: ", "", value)
    value <- gsub("\\,", "", value)
    value_split <- unlist(strsplit(value, split = " "))
    bytes <- as.numeric(value_split[1]) * switch(
      value_split[2],
      "KB" = 1e03,
      "MB" = 1e06,
      "GB" = 1e09
    )
  } else if(OS == "linux"){ 
    info_split <- strsplit(system("free", intern = TRUE), split = " ")
    info_split <- lapply(info_split, function(x){gsub("Mem:", "", x)})
    info_split <- lapply(info_split, function(x){gsub("Swap:", "", x)})
    info_split <- lapply(info_split, function(x){x[x != ""]})
    info_split <- do.call(rbind, info_split[1:2])
    bytes <- as.numeric(info_split[2, info_split[1,] == "free"])
  } else { # Mac
    system_info <- system("top -l 1 -s 0 | grep PhysMem", intern = TRUE)
    unused <- gsub(" .*,", "", system_info)
    value <- gsub("PhysMem: ", "", unused)
    value <- gsub(" unused.", "", value)
    if(grepl("M", value)){
      bytes <- as.numeric(gsub("M", "", value)) * 1e06
    }else if(grepl("G", value)){
      bytes <- as.numeric(gsub("G", "", value)) * 1e09
    }else if(grepl("K", value)){
      bytes <- as.numeric(gsub("K", "", value)) * 1e03
    }
  }
  return(bytes)

}

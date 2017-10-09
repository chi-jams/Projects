
package main

import (
     "os"
     "fmt"
)

func main() {
    fmt.Println(os.Args)
    fmt.Println(len(os.Args))
}

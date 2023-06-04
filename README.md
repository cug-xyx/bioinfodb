bioinfodb
================

这是一个Rcpp函数的尝试。

## 安装方法

``` r
devtools::install_github('cug-xyx/bioinfodb')
```

## `readOboFile`函数使用方法:

``` r
library(bioinfodb)

system.time({
  df = bioinfodb::readOboFile('data-raw/go-basic.obo')
})
```

    ## 用户 系统 流逝 
    ## 0.19 0.10 0.28

## 结果展示

``` r
tibble::as_tibble(df)
```

    ## # A tibble: 47,497 x 3
    ##    GO         Description                                              level    
    ##    <chr>      <chr>                                                    <chr>    
    ##  1 GO:0000001 mitochondrion inheritance                                biologic~
    ##  2 GO:0000002 mitochondrial genome maintenance                         biologic~
    ##  3 GO:0000003 reproduction                                             biologic~
    ##  4 GO:0000005 obsolete ribosomal chaperone activity                    molecula~
    ##  5 GO:0000006 high-affinity zinc transmembrane transporter activity    molecula~
    ##  6 GO:0000007 low-affinity zinc ion transmembrane transporter activity molecula~
    ##  7 GO:0000008 obsolete thioredoxin                                     molecula~
    ##  8 GO:0000009 alpha-1,6-mannosyltransferase activity                   molecula~
    ##  9 GO:0000010 trans-hexaprenyltranstransferase activity                molecula~
    ## 10 GO:0000011 vacuole inheritance                                      biologic~
    ## # ... with 47,487 more rows

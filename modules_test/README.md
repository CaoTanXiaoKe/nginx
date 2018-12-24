### 编译&安装
1. 利用 configure 脚本将定制的模块加入到 Ngnix 中：

`cd /usr/src/nginx/`

```
./configure --user=nginx --group=nginx --prefix=/etc/nginx --sbin-path=/usr/sbin/nginx --conf-path=/etc/nginx/nginx.conf --pid-path=/var/run/nginx.pid --lock-path=/var/run/nginx.lock --error-log-path=/var/log/nginx/error.log --http-log-path=/var/log/nginx/access.log --with-http_gzip_static_module --with-http_stub_status_module --with-http_ssl_module --with-pcre --with-file-aio --with-http_realip_module --without-http_scgi_module --without-http_uwsgi_module --with-http_realip_module --add-module=/usr/src/nginx/modules_test/daytime --add-module=/usr/src/nginx/modules_test/visit_count --add-module=/usr/src/nginx/modules_test/sent_a_file --add-module=/usr/src/nginx/modules_test/proxy_baidu --add-module=/usr/src/nginx/modules_test/sina_stock --add-module=/usr/src/nginx/modules_test/add_prefix_filter --with-debug
```

2. 编译&链接
```
make
```

3. 移动文件
```
make install
```


#### 依赖的第三方库：
```
epel-release
zlib zlib-devel 
pcre prce-devel 
openssl openssl-devel
```

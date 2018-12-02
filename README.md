#### 目的
这个仓库主要记录我阅读和学习Nginx源码的历程，主要包括一些笔记(notes文件夹下)，
对源码的一些注释，学习过程中开发的模块，以及对源代码的改动。 总之，这是一个
自娱自乐的练习仓库。

#### 文档&环境
- Nginx版本：1.14.0 
- Nginx 官网文档: http://nginx.org
- 我的机器：腾讯云CVM： Linux VM_16_22_centos 3.10.0-862.el7.x86_64
- 参考资料
     - [Nginx开发从入门到精通](http://tengine.taobao.org/book/)
     - 《深入理解Nginx (第二版)》陶辉

#### 下载&编译&安装
1. 更新软件库
```
yum update -y
```

2. 安装 EPEL库
```
yum install epel-release -y
```

3. 安装其他依赖
```
yum install -y zlib zlib-devel pcre prce-devel openssl openssl-devel
```

4. 下载&解压Nginx
```
cd /usr/src
wget https://nginx.org/download/nginx-1.14.0.tar.gz
tar xvf nginx-1.14.0.tar.gz
cd nginx-1.14.0
```

5. 创建 nginx 用户
```
useradd -d /etc/nginx/ -s /sbin/nologin nginx
```

6. 执行 configure 脚本
```
./configure --user=nginx --group=nginx --prefix=/etc/nginx --sbin-path=/usr/sbin/nginx --conf-path=/etc/nginx/nginx.conf --pid-path=/var/run/nginx.pid --lock-path=/var/run/nginx.lock --error-log-path=/var/log/nginx/error.log --http-log-path=/var/log/nginx/access.log --with-http_gzip_static_module --with-http_stub_status_module --with-http_ssl_module --with-pcre --with-file-aio --with-http_realip_module --without-http_scgi_module --without-http_uwsgi_module --with-http_realip_module
```

7. 编译&安装
```
make
make install
```

8. 检查是否已成功安装
```
nginx -v
```

9. 添加到 systemd service 文件(从而用 `systemctl` 进行管理)
```
vi /etc/systemd/system/nginx.service

[Unit]
Description=The NGINX HTTP and reverse proxy server
After=syslog.target network.target remote-fs.target nss-lookup.target

[Service]
Type=forking
PIDFile=/var/run/nginx.pid
ExecStartPre=/usr/sbin/nginx -t
ExecStart=/usr/sbin/nginx
ExecReload=/usr/sbin/nginx -s reload
ExecStop=/bin/kill -s QUIT $MAINPID
PrivateTmp=true

[Install]
WantedBy=multi-user.target
```

10. 启动 nginx 服务
```
systemctl enable nginx
systemctl start nginx
```

11. 检验 nginx是否已成功启动
```
curl localhost
```

12. (如果没有成功启动)确保防火墙允许访问 80 端口
```
firewall-cmd --zone=public --add-port=80/tcp --permanent && firewall-cmd --reload
```


func-example.o:     file format elf32-i386


Disassembly of section .text:

00000000 <woof>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 18             	sub    $0x18,%esp
   6:	a1 00 00 00 00       	mov    0x0,%eax
   b:	89 c2                	mov    %eax,%edx
   d:	b8 00 00 00 00       	mov    $0x0,%eax
  12:	89 54 24 0c          	mov    %edx,0xc(%esp)
  16:	c7 44 24 08 2b 00 00 	movl   $0x2b,0x8(%esp)
  1d:	00 
  1e:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  25:	00 
  26:	89 04 24             	mov    %eax,(%esp)
  29:	e8 fc ff ff ff       	call   2a <woof+0x2a>
  2e:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
  35:	e8 fc ff ff ff       	call   36 <woof+0x36>

0000003a <bar>:
  3a:	55                   	push   %ebp
  3b:	89 e5                	mov    %esp,%ebp
  3d:	53                   	push   %ebx
  3e:	83 ec 34             	sub    $0x34,%esp
  41:	89 e1                	mov    %esp,%ecx
  43:	ba 2c 00 00 00       	mov    $0x2c,%edx
  48:	a1 00 00 00 00       	mov    0x0,%eax
  4d:	89 4c 24 08          	mov    %ecx,0x8(%esp)
  51:	89 54 24 04          	mov    %edx,0x4(%esp)
  55:	89 04 24             	mov    %eax,(%esp)
  58:	e8 fc ff ff ff       	call   59 <bar+0x1f>
  5d:	a1 00 00 00 00       	mov    0x0,%eax
  62:	89 c2                	mov    %eax,%edx
  64:	b8 41 00 00 00       	mov    $0x41,%eax
  69:	89 54 24 0c          	mov    %edx,0xc(%esp)
  6d:	c7 44 24 08 0a 00 00 	movl   $0xa,0x8(%esp)
  74:	00 
  75:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  7c:	00 
  7d:	89 04 24             	mov    %eax,(%esp)
  80:	e8 fc ff ff ff       	call   81 <bar+0x47>
  85:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  8c:	eb 40                	jmp    ce <bar+0x94>
  8e:	8b 45 f0             	mov    -0x10(%ebp),%eax
  91:	8b 4c 85 f4          	mov    -0xc(%ebp,%eax,4),%ecx
  95:	8b 45 f0             	mov    -0x10(%ebp),%eax
  98:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
  9f:	8d 45 f4             	lea    -0xc(%ebp),%eax
  a2:	8d 1c 10             	lea    (%eax,%edx,1),%ebx
  a5:	ba 4c 00 00 00       	mov    $0x4c,%edx
  aa:	a1 00 00 00 00       	mov    0x0,%eax
  af:	89 4c 24 10          	mov    %ecx,0x10(%esp)
  b3:	89 5c 24 0c          	mov    %ebx,0xc(%esp)
  b7:	8b 4d f0             	mov    -0x10(%ebp),%ecx
  ba:	89 4c 24 08          	mov    %ecx,0x8(%esp)
  be:	89 54 24 04          	mov    %edx,0x4(%esp)
  c2:	89 04 24             	mov    %eax,(%esp)
  c5:	e8 fc ff ff ff       	call   c6 <bar+0x8c>
  ca:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  ce:	83 7d f0 05          	cmpl   $0x5,-0x10(%ebp)
  d2:	7e ba                	jle    8e <bar+0x54>
  d4:	b8 00 00 00 00       	mov    $0x0,%eax
  d9:	89 45 04             	mov    %eax,0x4(%ebp)
  dc:	8b 4d 04             	mov    0x4(%ebp),%ecx
  df:	ba 64 00 00 00       	mov    $0x64,%edx
  e4:	a1 00 00 00 00       	mov    0x0,%eax
  e9:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  ed:	8b 4d f0             	mov    -0x10(%ebp),%ecx
  f0:	89 4c 24 08          	mov    %ecx,0x8(%esp)
  f4:	89 54 24 04          	mov    %edx,0x4(%esp)
  f8:	89 04 24             	mov    %eax,(%esp)
  fb:	e8 fc ff ff ff       	call   fc <bar+0xc2>
 100:	83 c4 34             	add    $0x34,%esp
 103:	5b                   	pop    %ebx
 104:	5d                   	pop    %ebp
 105:	c3                   	ret    

00000106 <foo>:
 106:	55                   	push   %ebp
 107:	89 e5                	mov    %esp,%ebp
 109:	53                   	push   %ebx
 10a:	83 ec 34             	sub    $0x34,%esp
 10d:	ba 80 00 00 00       	mov    $0x80,%edx
 112:	a1 00 00 00 00       	mov    0x0,%eax
 117:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 11e:	89 54 24 04          	mov    %edx,0x4(%esp)
 122:	89 04 24             	mov    %eax,(%esp)
 125:	e8 fc ff ff ff       	call   126 <foo+0x20>
 12a:	89 e1                	mov    %esp,%ecx
 12c:	ba 2c 00 00 00       	mov    $0x2c,%edx
 131:	a1 00 00 00 00       	mov    0x0,%eax
 136:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 13a:	89 54 24 04          	mov    %edx,0x4(%esp)
 13e:	89 04 24             	mov    %eax,(%esp)
 141:	e8 fc ff ff ff       	call   142 <foo+0x3c>
 146:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 14d:	eb 40                	jmp    18f <foo+0x89>
 14f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 152:	8b 4c 85 f4          	mov    -0xc(%ebp,%eax,4),%ecx
 156:	8b 45 f0             	mov    -0x10(%ebp),%eax
 159:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 160:	8d 45 f4             	lea    -0xc(%ebp),%eax
 163:	8d 1c 10             	lea    (%eax,%edx,1),%ebx
 166:	ba 8f 00 00 00       	mov    $0x8f,%edx
 16b:	a1 00 00 00 00       	mov    0x0,%eax
 170:	89 4c 24 10          	mov    %ecx,0x10(%esp)
 174:	89 5c 24 0c          	mov    %ebx,0xc(%esp)
 178:	8b 4d f0             	mov    -0x10(%ebp),%ecx
 17b:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 17f:	89 54 24 04          	mov    %edx,0x4(%esp)
 183:	89 04 24             	mov    %eax,(%esp)
 186:	e8 fc ff ff ff       	call   187 <foo+0x81>
 18b:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 18f:	83 7d f0 05          	cmpl   $0x5,-0x10(%ebp)
 193:	7e ba                	jle    14f <foo+0x49>
 195:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
 199:	7f 0e                	jg     1a9 <foo+0xa3>
 19b:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 1a2:	e8 fc ff ff ff       	call   1a3 <foo+0x9d>
 1a7:	eb 0e                	jmp    1b7 <foo+0xb1>
 1a9:	8b 45 08             	mov    0x8(%ebp),%eax
 1ac:	83 e8 01             	sub    $0x1,%eax
 1af:	89 04 24             	mov    %eax,(%esp)
 1b2:	e8 fc ff ff ff       	call   1b3 <foo+0xad>
 1b7:	ba a7 00 00 00       	mov    $0xa7,%edx
 1bc:	a1 00 00 00 00       	mov    0x0,%eax
 1c1:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1c4:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 1c8:	89 54 24 04          	mov    %edx,0x4(%esp)
 1cc:	89 04 24             	mov    %eax,(%esp)
 1cf:	e8 fc ff ff ff       	call   1d0 <foo+0xca>
 1d4:	83 c4 34             	add    $0x34,%esp
 1d7:	5b                   	pop    %ebx
 1d8:	5d                   	pop    %ebp
 1d9:	c3                   	ret    

000001da <main>:
 1da:	55                   	push   %ebp
 1db:	89 e5                	mov    %esp,%ebp
 1dd:	83 e4 f0             	and    $0xfffffff0,%esp
 1e0:	83 ec 10             	sub    $0x10,%esp
 1e3:	a1 00 00 00 00       	mov    0x0,%eax
 1e8:	89 c2                	mov    %eax,%edx
 1ea:	b8 b6 00 00 00       	mov    $0xb6,%eax
 1ef:	89 54 24 0c          	mov    %edx,0xc(%esp)
 1f3:	c7 44 24 08 0b 00 00 	movl   $0xb,0x8(%esp)
 1fa:	00 
 1fb:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 202:	00 
 203:	89 04 24             	mov    %eax,(%esp)
 206:	e8 fc ff ff ff       	call   207 <main+0x2d>
 20b:	89 e1                	mov    %esp,%ecx
 20d:	ba 2c 00 00 00       	mov    $0x2c,%edx
 212:	a1 00 00 00 00       	mov    0x0,%eax
 217:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 21b:	89 54 24 04          	mov    %edx,0x4(%esp)
 21f:	89 04 24             	mov    %eax,(%esp)
 222:	e8 fc ff ff ff       	call   223 <main+0x49>
 227:	ba c2 00 00 00       	mov    $0xc2,%edx
 22c:	a1 00 00 00 00       	mov    0x0,%eax
 231:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 238:	00 
 239:	89 54 24 04          	mov    %edx,0x4(%esp)
 23d:	89 04 24             	mov    %eax,(%esp)
 240:	e8 fc ff ff ff       	call   241 <main+0x67>
 245:	ba d0 00 00 00       	mov    $0xd0,%edx
 24a:	a1 00 00 00 00       	mov    0x0,%eax
 24f:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 256:	00 
 257:	89 54 24 04          	mov    %edx,0x4(%esp)
 25b:	89 04 24             	mov    %eax,(%esp)
 25e:	e8 fc ff ff ff       	call   25f <main+0x85>
 263:	ba dd 00 00 00       	mov    $0xdd,%edx
 268:	a1 00 00 00 00       	mov    0x0,%eax
 26d:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 274:	00 
 275:	89 54 24 04          	mov    %edx,0x4(%esp)
 279:	89 04 24             	mov    %eax,(%esp)
 27c:	e8 fc ff ff ff       	call   27d <main+0xa3>
 281:	ba ea 00 00 00       	mov    $0xea,%edx
 286:	a1 00 00 00 00       	mov    0x0,%eax
 28b:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 292:	00 
 293:	89 54 24 04          	mov    %edx,0x4(%esp)
 297:	89 04 24             	mov    %eax,(%esp)
 29a:	e8 fc ff ff ff       	call   29b <main+0xc1>
 29f:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 2a6:	e8 fc ff ff ff       	call   2a7 <main+0xcd>
 2ab:	c9                   	leave  
 2ac:	c3                   	ret    

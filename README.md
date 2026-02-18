# VOCAEND

Source code for a Pwn challenge used in hzlt!Game 2026 CTF. This repository is
intended for archival and publication on GitHub.

## 前言

这份 README 是 Codex 写的，不过这一段是零音亲自写的。作为 VOCAEND 的出题人，hzlt!Game 2026 的主办者，Project Hazelita 的管理员，其实零音自一开始就意识到 hzlt!Game 2026 应该没啥人气了。毕竟连主办方的零音也是 CTF 的新手，不过能让 Project Hazelita 社群中至少一部分人感受到欢乐，让出题人感觉到出爽了，其实目的已经达到了——所以即使服务器被提前关停（按量计费的服务器付不起米了），hzlt!Game 最终活跃人数远少于预期，其实零音还是蛮欣慰的。

零音偶尔、或者说经常，应该说是非常鄙夷那些所谓的老资历——零音并非讨厌有能力的人，而是那些让自己看起来很权威的人，或者说讨厌官僚主义——尤其是顶着所谓对技术的热爱的旗号来进行的官僚主义。零音向来都是讨厌这一点的——顶着自嘲的帽子便能对人傲慢，将人情味的社团变成冷冰冰的技术沙盒，将正常的学习定义为「传承/继承」，将管理体制塑造为逆向淘汰的血汗工厂。是的，零音自始至终都认为兴趣应当是自驱的而非督促的，一旦用 KPI 来管理爱好者们的兴趣，兴趣就变成了劳动。毕竟，Linux 社区从来不会因为 Linus Torvalds 一个月没提交代码就要清退他。而所谓的小团体却又将新人和老人划分为封闭的圈子，老人们通过独特的黑话来制造回忆，又与新人构建起一道社交防火墙——从而新人变成了老人们谈资的观众和耗材。

零音从未觉得最僵化的行政手段可以管理最自由的黑客精神。这也是为什么零音在 Project Hazelita 社群中始终强调共情与引导，而非控制与恐惧。零音讨厌说教、讨厌趾高气扬、讨厌「你完全没经历过我的人生，却在对我指手画脚」。hzlt!Game 2026 的一部分初衷源于此，但更多还是希望陪大家一起好好跨年。虽然零音为了这个 7 天的比赛忙了 20 天，高数作业一笔未动（不过期末还是考了 96 哈哈哈），但零音觉得很有意义就好了。至于会不会有 h!G27，一切看运气吧。

最后，VOCAEND 这首歌真的是神曲，大伙一定要听啊😭`data/` 文件夹下有社群群友想要对彼此说的话。大概就是这么多。

> Even if whole world fades away, I won't stop singing my heart out.

## Build

Requirements: GCC, make, libc, libm.

```sh
make
```

Output binary: `data/vocaend`

## Run (local)

The binary expects `song*.txt` to exist in the current working directory and
loads the flag from a local `flag` file.

```sh
echo 'flag{test}' > data/flag
cd data
./vocaend
```

To skip lyric delays:

```sh
VOCA_FAST=1 ./vocaend
```

## Docker

The provided `Dockerfile` builds and runs the service with `socat`:

```sh
docker build -t vocaend .
docker run --rm -p 9999:9999 -e GZCTF_FLAG=flag{test} vocaend
```

## Layout

- `src/` challenge source code
- `inc/` headers and lyric macros
- `data/` song text files and runtime artifacts
- `build/` build intermediates

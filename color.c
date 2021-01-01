/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	col(int c)
{
	int col[11];

	col[0] = 0x5a5b99;
	col[1] = 0x222952;
	col[2] = 0x5F772A;
	col[3] = 0xFFFFFF;
	col[4] = 0x000000;
	col[5] = 0x5e0101;
	col[6] = 0x499ac9;
	col[7] = 0x67f5d1;
	col[8] = 0xFFFEB9;
	col[9] = 0x9dff80;
	col[10] = 0x1b0424;
	return (col[c]);
}

int	energy_color(int n)
{
	int col[21];

	col[0] = 0xFF1F00;
	col[1] = 0xFF3D00;
	col[2] = 0xFF5C00;
	col[3] = 0xFF7A00;
	col[4] = 0xFF9900;
	col[5] = 0xFFB800;
	col[6] = 0xFFD600;
	col[7] = 0xFFF500;
	col[8] = 0xEBFF00;
	col[9] = 0xCCFF00;
	col[10] = 0xADFF00;
	col[11] = 0x8FFF00;
	col[12] = 0x70FF00;
	col[13] = 0x52FF00;
	col[14] = 0x33FF00;
	col[15] = 0x14FF00;
	col[16] = 0x00FF0A;
	col[17] = 0x00FA0A;
	col[18] = 0x00F50A;
	col[19] = 0x00F009;
	col[20] = 0x00EB09;
	return (col[n]);
}

int	green3(int row)
{
	int	n[57];

	n[37] = 0x006318;
	n[38] = 0x006619;
	n[39] = 0x00691A;
	n[40] = 0x006B1A;
	n[41] = 0x006E1B;
	n[42] = 0x00701B;
	n[43] = 0x00731C;
	n[44] = 0x00751D;
	n[45] = 0x00781D;
	n[46] = 0x007A1E;
	n[47] = 0x007D1F;
	n[48] = 0x00801F;
	n[49] = 0x008220;
	n[50] = 0x008520;
	n[51] = 0x008721;
	n[52] = 0x008A22;
	n[53] = 0x008C22;
	n[54] = 0x008F23;
	n[55] = 0x009124;
	n[56] = 0x009424;
	if (row > 56)
		row = 56;
	return (n[row]);
}

int	green2(int row)
{
	int n[57];

	n[17] = 0x00300C;
	n[18] = 0x00330C;
	n[19] = 0x00360D;
	n[20] = 0x00380E;
	n[21] = 0x003B0E;
	n[22] = 0x003D0F;
	n[23] = 0x004010;
	n[24] = 0x004210;
	n[25] = 0x004511;
	n[26] = 0x004711;
	n[27] = 0x004A12;
	n[28] = 0x004D13;
	n[29] = 0x004F13;
	n[30] = 0x005214;
	n[31] = 0x005415;
	n[32] = 0x005715;
	n[33] = 0x005916;
	n[34] = 0x005C16;
	n[35] = 0x005E17;
	n[36] = 0x006118;
	if (row > 36)
		return (green3(row));
	return (n[row]);
}

int	greenwalls(int row)
{
	int	n[57];

	n[0] = 0x000501;
	n[1] = 0x000802;
	n[2] = 0x000A02;
	n[3] = 0x000D03;
	n[4] = 0x000F04;
	n[5] = 0x001204;
	n[6] = 0x001405;
	n[7] = 0x001706;
	n[8] = 0x001906;
	n[9] = 0x001C07;
	n[10] = 0x001F07;
	n[11] = 0x002108;
	n[12] = 0x002409;
	n[13] = 0x002609;
	n[14] = 0x00290A;
	n[15] = 0x002B0B;
	n[16] = 0x002E0B;
	if (row < 0)
		row = 0;
	if (row > 16)
		return (green2(row));
	return (n[row]);
}
